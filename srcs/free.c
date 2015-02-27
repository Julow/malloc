/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/10 23:16:33 by jaguillo          #+#    #+#             */
/*   Updated: 2015/02/27 15:04:12 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include <sys/mman.h>

static void		remove_chunk(t_freed *res)
{
	if (res->chunk->prev == NULL)
		res->zone->chunk = NULL;
	else
		res->chunk->prev->next = res->chunk->next;
	if (res->chunk->next != NULL)
		res->chunk->next->prev = res->chunk->prev;
	munmap(res->chunk, res->chunk->size + sizeof(t_chunk));
}

void			free_alloc(t_freed *res)
{
	if (res->alloc == res->chunk->first)
		res->chunk->first = (res->alloc->next) ? NEXT_ALLOC(res->alloc) : NULL;
	else
	{
		PREV_ALLOC(res->alloc)->next += res->alloc->next;
		NEXT_ALLOC(res->alloc)->prev += res->alloc->prev;
	}
	if (res->chunk != res->zone->chunk || res->zone->chunk_size == 0)
		remove_chunk(res);
}

void			free(void *ptr)
{
	t_freed			res;

	if (!search_alloc(&res, ptr))
		return ;
	free_alloc(&res);
}
