/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_search.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/12 13:10:16 by jaguillo          #+#    #+#             */
/*   Updated: 2015/02/12 18:48:29 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static int		insert_alloc(t_freed *res, t_alloc *prev, t_uint size)
{
	res->alloc = INSERT_ALLOC(prev);
	*(res->alloc) = ALLOC(size, prev->size, prev->next);
	if (prev->next != 0)
		res->alloc->next -= V(NEXT_ALLOC(prev)) - V(res->alloc);
	prev->next = V(res->alloc) - V(prev);
	res->chunk->free -= size;
	return (1);
}

static int		reuse_alloc(t_freed *res, t_alloc *all, t_uint size)
{
	res->alloc = all;
	all->size = size;
	return (1);
}

static int		chunk_first(t_freed *res, t_uint size)
{
	res->alloc = CHUNK_START(res->chunk);
	*(res->alloc) = ALLOC(size, 0, 0);
	res->chunk->first = res->alloc;
	return (1);
}

static int		chunk_end(t_freed *res, t_alloc *last, t_uint size)
{
	t_uint			max_free;

	max_free = res->chunk->size - (V(last) + last->size - V(res->chunk));
	if (max_free > res->chunk->free)
		res->chunk->free = max_free;
	if (max_free >= size)
		return (insert_alloc(res, last, size));
	return (0);
}

int				chunk_search(t_freed *res, t_uint size)
{
	t_alloc			*all;
	t_uint			tmp;
	t_uint			max_free;

	if (res->chunk->first == NULL)
		return (chunk_first(res, size));
	max_free = 0;
	all = res->chunk->first;
	while (all->next != 0)
	{
		tmp = all->next - all->size;
		if (MASK(all->flags, FLAG_FREE) && (tmp + all->size) >= size)
			return ((res->chunk->free -= tmp), reuse_alloc(res, all, size));
		if (tmp >= size)
			return (insert_alloc(res, all, size));
		if (tmp > max_free)
			max_free = tmp;
		all = NEXT_ALLOC(all);
	}
	res->chunk->free = max_free;
	return (chunk_end(res, all, size));
}
