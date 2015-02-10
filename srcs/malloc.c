/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/09 16:19:07 by jaguillo          #+#    #+#             */
/*   Updated: 2015/02/10 20:09:56 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void			*malloc(size_t size)
{
	t_freed			freed;

	if (size > MAX_SIZE)
		return (NULL);
	size = WORD(size + sizeof(t_alloc));
	search_freed(&freed, size);
	if (freed.alloc != NULL)
		return (V(freed.alloc) + sizeof(t_alloc));
	return (NULL);
}
