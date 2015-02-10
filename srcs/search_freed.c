/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_freed.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/10 13:12:11 by jaguillo          #+#    #+#             */
/*   Updated: 2015/02/10 15:37:49 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
/*
static int		chunk_search(t_freed *res)
{
	size_t			max_free;
	size_t			tmp;

	if (res->chunk->first == NULL ||
		(V(res->chunk->first) - V(res->chunk->start)) >= size)
		return (1);
	max_free = 0;
	res->prev = res->chunk->first;
	while (res->prev->next != NULL)
	{
		tmp = V(res->prev->next) - V(res->prev) - res->prev->size;
		if (tmp >= size)
			return (1);
		if (tmp > max_free)
			max_free = tmp;
		res->prev = res->prev->next;
	}
	res->chunk->free = max_free;
	if ((V(res->prev) + V(res->prev->size) + size) <= res->chunk->size)
		return (1);
	res->prev = NULL;
	return (0);
}

static void		zone_search(t_freed *res)
{
	t_alloc			**tmp;

	tmp = NULL;
	res->chunk = zone->chunk;
	while (chunk != NULL)
	{
		if (res->chunk->free >= res->size)
		{
			if (chunk_search(res))
			{
				res->chunk->free -= res->size;
				res->flags |= BIT(0);
				return ;
			}
		}
		res->chunk = res->chunk->next;
	}
	res->chunk = NULL; // TODO: Create chunk
}

void			search_freed(t_freed *res, size_t size)
{
	extern t_env	g_env;
	int				i;

	*res = (t_freed){0, size, NULL, NULL, NULL};
	i = -1;
	while (++i < ZONE_COUNT)
	{
		res->zone = &(g_env.zone[i]);
		if (res->zone.min > size || size > res->zone.max)
			continue ;
		zone_search(res);
		if (ISBIT(res->flags, 0))
			return ;
	}
	res->zone = NULL;
}
*/

static int		chunk_search(t_freed *res, size_t size)
{
	const void		*chunk_end = res->chunk->start + res->chunk->size;
	t_alloc			*tmp;

	if (res->chunk->first == NULL)
	{
		res->alloc = res->chunk->start;
		*(res->alloc) = (t_alloc){size, 0, size};
		res->chunk->first = res->alloc;
		return (1);
	}
	tmp = res->alloc;
	while (NEXT_ALLOC(tmp) < chunk_end)
	{
		if ()
	}
	return (0);
}

static int		chunk_create(t_freed *res, size_t size)
{
	// TODO
	(void)res;
	(void)size;
	return (0);
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
		if (size < res->zone.min || size > res->zone.max)
			continue ;
		if (zone_search(res, size))
			return ;
	}
	res->zone = NULL;
}
