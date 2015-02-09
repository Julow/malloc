/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/09 17:44:04 by jaguillo          #+#    #+#             */
/*   Updated: 2015/02/09 18:09:30 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

#define INIT_ALLOC		{0, NULL}
#define INIT_CHUNK		{NULL, 0, ARRAY(CHUNK_PER_ZONE, INIT_ALLOC)}
#define INIT_ZONE(n,m)	(t_zone){n, m, ARRAY(CHUNK_PER_ZONE, INIT_CHUNK)}

t_env			g_env = {
	INIT_ZONE(TINY_MIN, TINY_MAX),
	INIT_ZONE(SMALL_MIN, SMALL_MAX),
	INIT_ZONE(LARGE_MIN, LARGE_MAX)
};
