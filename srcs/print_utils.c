/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/10 18:04:32 by jaguillo          #+#    #+#             */
/*   Updated: 2015/02/10 21:25:44 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include <unistd.h>

#define PUTNBR_BUFF		41

int				ft_putstr(const char *str)
{
	int				len;

	len = -1;
	while (str[++len] != '\0')
		;
	return (write(1, str, len));
}

int				ft_putulong(t_ulong n)
{
	char			nb[PUTNBR_BUFF];
	size_t			i;

	i = PUTNBR_BUFF;
	while (n != 0)
	{
		nb[--i] = '0' + (n % 10);
		n /= 10;
	}
	return (write(1, nb + i, PUTNBR_BUFF - i));
}

int				ft_putexa(t_ulong exa)
{
	const char		*base = "0123456789ABCDEF";
	char			nb[PUTNBR_BUFF];
	size_t			i;

	if (exa == 0)
		return (ft_putstr("NULL"));
	i = PUTNBR_BUFF;
	while (exa > 0)
	{
		nb[--i] = base[exa % 16];
		exa /= 16;
	}
	nb[--i] = 'x';
	nb[--i] = '0';
	return (write(1, nb + i, PUTNBR_BUFF - i));
}
