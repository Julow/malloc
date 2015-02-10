/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/09 17:44:04 by jaguillo          #+#    #+#             */
/*   Updated: 2015/02/10 20:26:45 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include <unistd.h>

#define INIT_ZONE(n,m,c)	(t_zone){0, n, m, c, NULL}

t_env			g_env = {
	{
		INIT_ZONE(TINY_MIN, TINY_MAX, TINY_CHUNK),
		INIT_ZONE(SMALL_MIN, SMALL_MAX, SMALL_CHUNK),
		INIT_ZONE(LARGE_MIN, LARGE_MAX, LARGE_CHUNK)
	},
	NULL,
	0
};

size_t			ft_umax(size_t a, size_t b)
{
	if (a > b)
		return (a);
	return (b);
}

size_t			page_round(size_t size)
{
	extern t_env	g_env;

	if (g_env.page_size == 0)
		g_env.page_size = (size_t)getpagesize();
	return ((size + g_env.page_size - 1) / g_env.page_size * g_env.page_size);
}
