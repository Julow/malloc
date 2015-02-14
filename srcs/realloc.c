/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/10 23:17:48 by jaguillo          #+#    #+#             */
/*   Updated: 2015/02/14 00:00:26 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static int		try_extend_left(t_freed *all, t_uint right, t_uint size)
{
	t_uint			left;
	t_alloc			*moved;

	if (all->alloc->prev == 0)
		left = V(all->alloc) - CHUNK_START(all->chunk);
	else
		left = all->alloc->prev - PREV_ALLOC(all->alloc)->size;
	if ((left + right) < size)
		return (0);
	moved = V(all->alloc) - left;
	ft_memmove(moved, V(all->alloc), MIN(size, all->alloc->size));
	moved->size = size;
	all->alloc = moved;
	return (1);
}

static int		try_extend(t_freed *all, t_uint size)
{
	t_uint			right;

	if (all->alloc->next == 0)
		right = CHUNK_END(all->chunk) - V(all->alloc);
	else
		right = all->alloc->next;
	if (right >= size)
		return ((all->alloc->size = size), 1);
	return (try_extend_left(all, right, size));
}

static int		try_remalloc(t_freed *res, t_uint size)
{
	t_freed			freed;

	search_freed(&freed, (t_uint)size);
	if (freed.alloc == NULL)
		return (0);
	ft_memcpy(MEM_ALLOC(freed.alloc), MEM_ALLOC(res->alloc),
		MIN(size, res->alloc->size));
	free_alloc(res);
	*res = freed;
	return (1);
}

void			*realloc(void *ptr, size_t size)
{
	t_freed			res;

	if (ptr == NULL)
		return (malloc(size));
	else if (size == 0)
		return (free(ptr), NULL);
	if (size < MIN_SIZE || size > MAX_SIZE)
		return (NULL);
	if (!search_alloc(&res, ptr))
		return (NULL);
	size = WORD(size + sizeof(t_alloc));
	if (try_extend(&res, (t_uint)size))
		return (MEM_ALLOC(res.alloc));
	if (try_remalloc(&res, (t_uint)size))
		return (MEM_ALLOC(res.alloc));
	return (NULL);
}
