/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/19 21:24:39 by jaguillo          #+#    #+#             */
/*   Updated: 2015/01/20 14:37:43 by jaguillo         ###   ########.fr       */
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
	if (last->ptr == ptr)
		return ((zone->first = last->next), 1);
	tmp = last->next;
	while (tmp != NULL)
	{
		if (tmp->ptr == ptr)
			return ((last->next = tmp->next), 1);
		last = tmp;
		tmp = tmp->next;
	}
	// Error: Double free
	return (1);
}

static int		free_large(void *ptr)
{
	extern t_env	g_env;
	t_malloc		*tmp;
	t_malloc		*last;

	last = g_env.large.first;
	if (last->ptr == ptr)
		return ((g_env.large.first = last->next), munmap(last, last->length), 1);
	tmp = last->next;
	while (tmp != NULL)
	{
		if (tmp->ptr == ptr)
			return ((last->next = tmp->next), munmap(tmp, tmp->length), 1);
		last = tmp;
		tmp = tmp->next;
	}
	// Error: Never malloc
	return (0);
}

void			free(void *ptr)
{
	extern t_env	g_env;

	if (ptr == NULL)
		return ;
	if (free_zone(ptr, &(g_env.tiny)) || free_zone(ptr, &(g_env.small)))
		return ;
	free_large(ptr);
}
