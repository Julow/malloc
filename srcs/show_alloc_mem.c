/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/10 21:02:29 by jaguillo          #+#    #+#             */
/*   Updated: 2015/02/10 23:30:56 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static t_ulong	print_alloc(t_alloc *alloc, int flags)
{
	t_ulong			size;

	size = alloc->size - sizeof(t_alloc);
	ft_putexa((t_ulong)(V(alloc) + sizeof(t_alloc)));
	ft_putstr(" - ");
	ft_putexa((t_ulong)INSERT_ALLOC(alloc));
	ft_putstr(" : ");
	ft_putulong(size);
	ft_putstr(" octets\n");
	(void)flags;
	return (size);
}

static t_ulong	print_chunk(t_chunk *chunk, int flags)
{
	t_ulong			total;
	t_alloc			*alloc;

	if (MASK(flags, DEBUG_CHUNK))
	{
		ft_putstr("chunk ");
		ft_putexa((t_ulong)chunk->start);
		ft_putstr(" : ");
		ft_putulong((t_ulong)chunk->size);
		while (MASK(flags, DEBUG_FREE) && ft_putstr(" (")
			&& ft_putulong((t_ulong)chunk->free) && ft_putstr(" free)\n") && 0);
	}
	alloc = chunk->first;
	total = 0;
	while (alloc != NULL)
	{
		total += print_alloc(alloc, flags);
		if (alloc->next == 0)
			break ;
		alloc = NEXT_ALLOC(alloc);
	}
	while (MASK(flags, DEBUG_CHUNK) && ft_putstr("\n") && 0);
	return (total);
}

static t_ulong	print_zone(t_zone *zone, const char *name, int flags)
{
	t_ulong			total;
	t_chunk			*chunk;

	chunk = zone->chunk;
	total = 0;
	ft_putstr(name);
	ft_putstr(" : ");
	ft_putexa((chunk == NULL) ? 0 : (t_ulong)chunk);
	ft_putstr("\n");
	while (chunk != NULL)
	{
		total += print_chunk(chunk, flags);
		chunk = chunk->next;
	}
	return (total);
}

void			show_alloc_debug(int flags)
{
	extern t_env	g_env;
	t_ulong			total;

	while (MASK(flags, DEBUG_INFO) && ft_putstr("Page size: ")
		&& ft_putulong(g_env.page_size) && ft_putstr("\nLast map: ")
		&& ft_putulong((t_ulong)g_env.last_map) && ft_putstr("\n\n") && 0);
	total = print_zone(&(g_env.zone[0]), "TINY", flags);
	total += print_zone(&(g_env.zone[1]), "SMALL", flags);
	total += print_zone(&(g_env.zone[2]), "LARGE", flags);
	ft_putstr("Total : ");
	ft_putulong(total);
	ft_putstr(" octets\n");
}

void			show_alloc_mem(void)
{
	show_alloc_debug(0);
}
