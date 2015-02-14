/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/09 16:19:07 by jaguillo          #+#    #+#             */
/*   Updated: 2015/02/14 00:00:37 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void			*malloc(size_t size)
{
	t_freed			freed;

	if (size < MIN_SIZE || size > MAX_SIZE)
		return (NULL);
	size = WORD(size + sizeof(t_alloc));
	search_freed(&freed, (t_uint)size);
	if (freed.alloc != NULL)
		return (MEM_ALLOC(freed.alloc));
	return (NULL);
}
