/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_alloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/12 14:56:38 by jaguillo          #+#    #+#             */
/*   Updated: 2015/02/13 17:32:05 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static int		search_in_chunk(t_freed *res, void *ptr)
{
	t_alloc			*all;

	all = res->chunk->first;
	if (all == NULL)
		return (0);
	while (1)
	{
		if (ptr >= V(all) && ptr < (V(all) + all->size))
			return ((res->alloc = all), 1);
		if (all->next == 0)
			return (0);
		all = NEXT_ALLOC(all);
	}
}

static int		search_in_zone(t_freed *res, void *ptr)
{
	t_chunk			*chunk;

	chunk = res->zone->chunk;
	while (chunk != NULL)
	{
		if (ptr >= CHUNK_START(chunk)
			&& ptr <= (CHUNK_START(chunk) + chunk->size))
		{
			res->chunk = chunk;
			if (search_in_chunk(res, ptr))
				return (1);
		}
		chunk = chunk->next;
	}
	return (0);
}

int				search_alloc(t_freed *res, void *ptr)
{
	extern t_env	g_env;
	int				i;

	*res = (t_freed){NULL, NULL, NULL};
	i = -1;
	while (++i < ZONE_COUNT)
	{
		res->zone = &(g_env.zone[i]);
		if (search_in_zone(res, ptr))
			return (1);
	}
	res->zone = NULL;
	return (0);
}
