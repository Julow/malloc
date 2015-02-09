/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/19 21:23:31 by jaguillo          #+#    #+#             */
/*   Updated: 2015/01/20 18:02:13 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include <sys/mman.h>

static void		*malloc_zone(t_zone *zone, int size)
{
	t_malloc		*tmp;
	t_malloc		*i;

	if (zone->start == NULL)
		zone->start = mmap(NULL, page_round(zone->size), MMAP_PROT, MMAP_FLAG, 0, 0);
	if (zone->start == MAP_FAILED)
		return (NULL);
	if (zone->first == NULL || ((void*)zone->first - zone->start) >= size)
	{
		tmp = (t_malloc*)(zone->start);
		*tmp = MALLOC(size, zone->first);
		return ((zone->first = tmp), START(tmp));
	}
	i = zone->first;
	while (i->next != NULL)
	{
		if (((void*)i + i->length + size) < (void*)i->next)
		{
			tmp = (t_malloc*)((void*)i + i->length);
			*tmp = MALLOC(size, i->next);
			return ((i->next = tmp), START(tmp));
		}
		i = i->next;
	}
	if (((void*)i + i->length + size) > (zone->start + zone->size))
		return (NULL);
	tmp = (t_malloc*)((void*)i + i->length);
	*tmp = MALLOC(size, i->next);
	return ((i->next = tmp), START(tmp));
}

void			*malloc(size_t size)
{
	extern t_env	g_env;
	void			*ptr;

	ptr = NULL;
	size += sizeof(t_malloc);
	if (size <= TINY_MAX && (ptr = malloc_zone(&(g_env.tiny), size)) != NULL)
		return (ptr);
	if (size <= SMALL_MAX && (ptr = malloc_zone(&(g_env.small), size)) != NULL)
		return (ptr);
	ptr = mmap(NULL, page_round(size), MMAP_PROT, MMAP_FLAG, 0, 0);
	if (ptr == MAP_FAILED)
		return (NULL);
	*((t_malloc*)ptr) = MALLOC(size, g_env.large.first);
	g_env.large.first = ptr;
	return (ptr);
}
