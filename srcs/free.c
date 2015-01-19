/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/19 21:24:39 by jaguillo          #+#    #+#             */
/*   Updated: 2015/01/19 23:41:58 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include <sys/mman.h>

extern t_env	g_env;

static int		free_zone(void *ptr, t_zone *zone)
{
	t_malloc		*tmp;
	t_malloc		*last;

	if (ptr < zone->min || ptr > zone->max)
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
	t_malloc		*tmp;
	t_malloc		*last;

	last = g_env.large;
	if (last->ptr == ptr)
		return ((g_env.large = last->next), munmap(last, last->length), 1);
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
	if (ptr == NULL)
		return ;
	if (free_zone(ptr, &(g_env.tiny)) || free_zone(ptr, &(g_env.small)))
		return ;
	free_large(ptr);
}
