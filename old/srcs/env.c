/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/20 15:49:16 by jaguillo          #+#    #+#             */
/*   Updated: 2015/02/09 15:57:09 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include <unistd.h>

t_env			g_env = {
	ZONE(TINY_SIZE),
	ZONE(SMALL_SIZE),
	ZONE(0)
};

size_t			page_round(size_t size)
{
	const int		page = getpagesize();

	return ((size + page - 1) / page * page);
}
