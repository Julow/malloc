/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/19 21:23:31 by jaguillo          #+#    #+#             */
/*   Updated: 2015/01/19 23:16:03 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static void		*malloc_zone(t_zone *zone, size_t size)
{
	t_malloc		*tmp;
	t_malloc		*i;

	if (zone->first == NULL || (zone->first - zone->min) >= size)
	{
		tmp = (t_malloc*)(zone->min);
		*tmp = (t_malloc){zone->min + sizeof(t_malloc), size, zone->first};
		return (tmp->ptr);
	}
	i = zone->first;
	while (i != NULL)
	{
		if ((i + i->length + size) < i->next)
		{
			tmp = (t_malloc*)(i + i->length);
			*tmp = (t_malloc){i + i->length + sizeof(t_malloc), size, i->next};
			i->next = tmp;
			return (tmp->ptr);
		}
		i = i->next;
	}
	return (NULL); // Not enougth space in zone
}

void			*malloc(size_t size)
{
	void			*ptr;

	if (size == 0)
		return (g_env.null);
	ptr = NULL;
	size += sizeof(t_malloc);
	if (size <= TINY_MAX && (ptr = malloc_zone(&(g_env.tiny), size)) != NULL)
		return (ptr);
	if (size <= SMALL_MAX && (ptr = malloc_zone(&(g_env.small), size)) != NULL)
		return (ptr);
	// TODO: malloc large
	return (NULL);
}
