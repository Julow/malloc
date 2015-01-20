/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/19 21:23:31 by jaguillo          #+#    #+#             */
/*   Updated: 2015/01/20 13:22:29 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include <sys/mman.h>

extern t_env	g_env;

static void		*malloc_zone(t_zone *zone, int size)
{
	t_malloc		*tmp;
	t_malloc		*i;

	if (zone->start == NULL)
		zone->start = mmap(NULL, zone->size, MMAP_PROT, MMAP_FLAG, 0, 0);
	if (zone->start == MAP_FAILED)
		return (NULL);
	if (zone->first == NULL || ((void*)zone->first - zone->start) >= size)
	{
		tmp = (t_malloc*)(zone->start);
		*tmp = (t_malloc){(void*)tmp + sizeof(t_malloc), size, zone->first};
		return (tmp->ptr);
	}
	i = zone->first;
	while (i->next != NULL)
	{
		if (((void*)i + i->length + size) < (void*)i->next)
		{
			tmp = (t_malloc*)((void*)i + i->length);
			*tmp = (t_malloc){(void*)tmp + sizeof(t_malloc), size, i->next};
			return ((i->next = tmp), tmp->ptr);
		}
		i = i->next;
	}
	if (((void*)i + i->length + size) > (zone->start + zone->size))
		return (NULL);
	tmp = (t_malloc*)((void*)i + i->length);
	*tmp = (t_malloc){(void*)tmp + sizeof(t_malloc), size, i->next};
	return ((i->next = tmp), tmp->ptr);
}

void			*malloc(size_t size)
{
	const int		page = getpagesize();
	void			*ptr;

	ptr = NULL;
	size = ((size + sizeof(t_malloc)) + page) / page * page;
	if (size <= TINY_MAX && (ptr = malloc_zone(&(g_env.tiny), size)) != NULL)
		return (ptr);
	if (size <= SMALL_MAX && (ptr = malloc_zone(&(g_env.small), size)) != NULL)
		return (ptr);
	ptr = mmap(NULL, size, MMAP_PROT, MMAP_FLAG, 0, 0);
	if (ptr == MAP_FAILED)
		return (NULL);
	*((t_malloc*)ptr) = (t_malloc){ptr + sizeof(t_malloc), size, g_env.large};
	g_env.large = ptr;
	return (ptr);
}
