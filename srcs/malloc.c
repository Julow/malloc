/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/09 16:19:07 by jaguillo          #+#    #+#             */
/*   Updated: 2015/02/10 15:12:21 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void			*malloc(size_t size)
{
	t_freed			freed;

	if (size > MAX_SIZE)
		return (NULL);
	size = (size + sizeof(t_alloc) + 3) / 4 * 4;
	search_mem(&freed, size + sizeof(t_alloc));
	if (!ISBIT(freed.flags, 0))
		return (NULL);
	return (NULL);
}
