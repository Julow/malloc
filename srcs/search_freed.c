/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_freed.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/10 13:12:11 by jaguillo          #+#    #+#             */
/*   Updated: 2015/02/12 13:10:25 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include <sys/mman.h>

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
