/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/13 23:56:12 by jaguillo          #+#    #+#             */
/*   Updated: 2015/02/13 23:59:21 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

typedef unsigned char	t_byte;

void			ft_memmove(void *dst, const void *src, t_uint len)
{
	if (src >= dst)
		return (ft_memcpy(dst, src, len));
	dst += len;
	src += len;
	while (len >= sizeof(t_ulong))
	{
		dst -= sizeof(t_ulong);
		src -= sizeof(t_ulong);
		*((t_ulong*)dst) = *((t_ulong*)src);
		len -= sizeof(t_ulong);
	}
	while (len > 0)
	{
		dst--;
		src--;
		*((t_byte*)dst) = *((t_byte*)src);
		len--;
	}
}

void			ft_memcpy(void *dst, const void *src, t_uint len)
{
	while (len >= sizeof(t_ulong))
	{
		*((t_ulong*)dst) = *((t_ulong*)src);
		dst += sizeof(t_ulong);
		src += sizeof(t_ulong);
		len -= sizeof(t_ulong);
	}
	while (len > 0)
	{
		*((t_byte*)dst) = *((t_byte*)src);
		dst++;
		src++;
		len--;
	}
}
