/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_freed.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/10 13:12:11 by jaguillo          #+#    #+#             */
/*   Updated: 2015/02/10 23:29:07 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include <sys/mman.h>

static int		chunk_search(t_freed *res, size_t size)
{
	t_alloc			*all;
	size_t			tmp;
	size_t			max_free;

	if (res->chunk->first == NULL)
	{
		res->alloc = res->chunk->start;
		*(res->alloc) = ALLOC(size, 0, 0);
		res->chunk->first = res->alloc;
		return (1);
	}
	max_free = 0;
	all = res->chunk->first;
	while (all->next != 0)
	{
		tmp = all->next - all->size;
		if (tmp >= size)
		{
			*INSERT_ALLOC(all) = ALLOC(size, all->size, all->next - all->size);
			all->next = all->size;
			NEXT_ALLOC(all)->prev = all->next - all->size;
			res->chunk->free -= size;
			return ((res->alloc = INSERT_ALLOC(all)), 1);
		}
		if (tmp > max_free)
			max_free = tmp;
		all = NEXT_ALLOC(all);
	}
	res->chunk->free = max_free;
	return (0);
}

static void		chunk_add(t_zone *zone, t_chunk *chunk)
{
	t_chunk			*tmp;

	tmp = zone->chunk;
	if (tmp == NULL)
	{
		zone->chunk = chunk;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = chunk;
}

static int		chunk_create(t_freed *res, size_t size)
{
	extern t_env	g_env;
	size_t			chunk_size;

	chunk_size = ft_umax(WORD(size + sizeof(t_chunk)), res->zone->chunk_size);
	if ((g_env.last_map = mmap(g_env.last_map, page_round(chunk_size),
		MMAP_PROT, MMAP_FLAG, -1, 0)) == MAP_FAILED)
		g_env.last_map = NULL;
	if ((res->chunk = g_env.last_map) != NULL)
	{
		res->chunk->start = V(res->chunk) + sizeof(t_chunk);
		res->chunk->size = V(res->chunk) + chunk_size - res->chunk->start;
		res->chunk->free = res->chunk->size;
		res->chunk->first = NULL;
		res->chunk->next = NULL;
		chunk_add(res->zone, res->chunk);
		chunk_search(res, size);
	}
	return (1);
}

static int		zone_search(t_freed *res, size_t size)
{
	if ((res->zone->chunk_size - sizeof(t_alloc)) <= size)
		return (chunk_create(res, size));
	res->chunk = res->zone->chunk;
	while (res->chunk != NULL)
	{
		if (res->chunk->free >= size && chunk_search(res, size))
			return (1);
		res->chunk = res->chunk->next;
	}
	return (chunk_create(res, size));
}

void			search_freed(t_freed *res, size_t size)
{
	extern t_env	g_env;
	int				i;

	*res = (t_freed){NULL, NULL, NULL};
	i = -1;
	while (++i < ZONE_COUNT)
	{
		res->zone = &(g_env.zone[i]);
		if (size < res->zone->min || size > res->zone->max)
			continue ;
		if (zone_search(res, size))
			return ;
	}
	res->zone = NULL;
}
