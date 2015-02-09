/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/19 21:24:39 by jaguillo          #+#    #+#             */
/*   Updated: 2015/01/20 17:59:33 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include <sys/mman.h>

static int		free_zone(void *ptr, t_zone *zone)
{
	t_malloc		*tmp;
	t_malloc		*last;

	if (ptr < zone->start || ptr > (zone->start + zone->size))
		return (0);
	last = zone->first;
	if ((void*)last == ptr)
		return ((zone->first = last->next), 1);
	tmp = last->next;
	while (tmp != NULL)
	{
		if ((void*)tmp == ptr)
			return ((last->next = tmp->next), 1);
		last = tmp;
		tmp = tmp->next;
	}
	return (1);
}

static int		free_large(void *ptr)
{
	extern t_env	g_env;
	t_malloc		*tmp;
	t_malloc		*last;

	last = g_env.large.first;
	if ((void*)last == ptr)
		return ((g_env.large.first = last->next), munmap(last, last->length));
	tmp = last->next;
	while (tmp != NULL)
	{
		if ((void*)tmp == ptr)
			return ((last->next = tmp->next), munmap(tmp, tmp->length));
		last = tmp;
		tmp = tmp->next;
	}
	return (0);
}

void			free(void *ptr)
{
	extern t_env	g_env;

	if (ptr == NULL)
		return ;
	ptr -= sizeof(t_malloc);
	if (free_zone(ptr, &(g_env.tiny)) || free_zone(ptr, &(g_env.small)))
		return ;
	free_large(ptr);
}
