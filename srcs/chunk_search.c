/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_search.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/12 13:10:16 by jaguillo          #+#    #+#             */
/*   Updated: 2015/02/12 13:47:20 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static int		insert_alloc(t_freed *res, t_alloc *prev, size_t size)
{
	res->alloc = INSERT_ALLOC(prev);
	*(res->alloc) = ALLOC(size, prev->size, prev->next);
	if (prev->next != 0)
		res->alloc->next -= V(NEXT_ALLOC(prev)) - V(res->alloc);
	prev->next = V(res->alloc) - V(prev);
	return (1);
}

static int		chunk_first(t_freed *res, size_t size)
{
	res->alloc = res->chunk->start;
	*(res->alloc) = ALLOC(size, 0, 0);
	res->chunk->first = res->alloc;
	return (1);
}

static int		chunk_end(t_freed *res, t_alloc *last, size_t size)
{
	size_t			max_free;

	max_free = res->chunk->size - (V(last) - res->chunk->start);
	if (max_free >= size)
	{
		max_free -= size;
		if (max_free > res->chunk->free)
			res->chunk->free = max_free;
		return (insert_alloc(res, last, size));
	}
	if (max_free > res->chunk->free)
		res->chunk->free = max_free;
	return (0);
}

int				chunk_search(t_freed *res, size_t size)
{
	t_alloc			*all;
	size_t			tmp;
	size_t			max_free;

	if (res->chunk->first == NULL)
		return (chunk_first(res, size));
	max_free = 0;
	all = res->chunk->first;
	while (all->next != 0)
	{
		tmp = all->next - all->size;
		if (tmp >= size)
		{
			res->chunk->free -= size;
			return (insert_alloc(res, all, size));
		}
		if (tmp > max_free)
			max_free = tmp;
		all = NEXT_ALLOC(all);
	}
	res->chunk->free = max_free;
	return (chunk_end(res, all, size));
}
