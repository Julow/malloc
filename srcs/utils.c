/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/09 17:44:04 by jaguillo          #+#    #+#             */
/*   Updated: 2015/02/10 09:33:44 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

#define INIT_ZONE(n,m,c)	(t_zone){0, n, m, c, NULL}

t_env			g_env = {
	{
		INIT_ZONE(TINY_MIN, TINY_MAX, TINY_CHUNK),
		INIT_ZONE(SMALL_MIN, SMALL_MAX, SMALL_CHUNK),
		INIT_ZONE(LARGE_MIN, LARGE_MAX, LARGE_CHUNK)
	}
};
