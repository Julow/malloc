/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/10 23:16:33 by jaguillo          #+#    #+#             */
/*   Updated: 2015/02/12 15:27:21 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void			free(void *ptr)
{
	t_freed			res;

	if (!search_alloc(&res, ptr))
		return ;
	res.alloc->flags |= FLAG_FREE;
	res.chunk->free += res.alloc->size;
	while (res.alloc->prev != 0
		&& MASK(PREV_ALLOC(res.alloc)->flags, FLAG_FREE))
		res.alloc = PREV_ALLOC(res.alloc);
	while (NEXT_ALLOC(res.alloc)->next != 0
		&& MASK(NEXT_ALLOC(res.alloc)->flags, FLAG_FREE))
		res.alloc->next += NEXT_ALLOC(res.alloc)->next;
	if (res.chunk->free < (res.alloc->next - sizeof(t_alloc)))
		res.chunk->free = res.alloc->next - sizeof(t_alloc);
}
