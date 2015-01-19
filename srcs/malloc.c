/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/19 21:23:31 by jaguillo          #+#    #+#             */
/*   Updated: 2015/01/19 23:44:32 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

extern t_env	g_env;

static void		*malloc_zone(t_zone *zone, int size)
{
	t_malloc		*tmp;
	t_malloc		*i;

	if (zone->first == NULL || ((void*)zone->first - zone->min) >= size)
	{
		tmp = (t_malloc*)(zone->min);
		*tmp = (t_malloc){(void*)zone->min + sizeof(t_malloc), size, zone->first};
		return (tmp->ptr);
	}
	i = zone->first;
	while (i->next != NULL)
	{
		if (((void*)i + i->length + size) < (void*)i->next)
		{
			tmp = (t_malloc*)((void*)i + i->length);
			*tmp = (t_malloc){(void*)i + i->length + sizeof(t_malloc), size, i->next};
			return ((i->next = tmp), tmp->ptr);
		}
		i = i->next;
	}
	if (((void*)i + i->length + size) > zone->max)
		return (NULL);
	tmp = (t_malloc*)((void*)i + i->length);
	*tmp = (t_malloc){(void*)i + i->length + sizeof(t_malloc), size, i->next};
	return ((i->next = tmp), tmp->ptr);
}

void			*malloc(size_t size)
{
	void			*ptr;

	ptr = NULL;
	size += sizeof(t_malloc);
	if (size <= TINY_MAX && (ptr = malloc_zone(&(g_env.tiny), size)) != NULL)
		return (ptr);
	if (size <= SMALL_MAX && (ptr = malloc_zone(&(g_env.small), size)) != NULL)
		return (ptr);
	// TODO: malloc large
	return (NULL);
}
