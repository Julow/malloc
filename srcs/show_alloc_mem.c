/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/20 13:29:15 by jaguillo          #+#    #+#             */
/*   Updated: 2015/01/20 14:37:35 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include <unistd.h>

static int		ft_putstr(char *str)
{
	int				len;

	len = -1;
	while (str[++len] != '\0')
		;
	return (write(1, str, len));
}

static int		ft_putnbr(int n)
{
	char			nb[21];
	size_t			i;

	i = 21;
	nb[0] = (n < 0) ? '-' : '+';
	if (n <= 0)
	{
		nb[--i] = '0' - (n % 10);
		n /= -10;
	}
	while (n != 0)
	{
		nb[--i] = '0' + (n % 10);
		n /= 10;
	}
	if (nb[0] == '-')
		nb[--i] = '-';
	return (write(1, nb + i, 21 - i));
}

static int		ft_putexa(t_ulong exa)
{
	const char		*base = "0123456789ABCDEF";
	char			nb[41];
	size_t			i;

	if (exa == 0)
		return (ft_putstr("EMPTY"));
	i = 41;
	while (exa > 0)
	{
		nb[--i] = base[exa % 16];
		exa /= 16;
	}
	return (write(1, nb + i, 41 - i));
}

static int		print_zone(char *name, t_zone *zone)
{
	int				total;
	t_malloc		*tmp;

	total = 0;
	ft_putstr(name);
	ft_putstr(" : ");
	ft_putexa((t_ulong)(zone->start));
	ft_putstr("\n");
	tmp = zone->first;
	while (tmp != NULL)
	{
		ft_putexa((t_ulong)(tmp->ptr));
		ft_putstr(" - ");
		ft_putexa((t_ulong)(tmp + tmp->length));
		ft_putstr(" : ");
		ft_putnbr(tmp->length - sizeof(t_malloc));
		ft_putstr(" octets\n");
		total += tmp->length - sizeof(t_malloc);
		tmp = tmp->next;
	}
	return (total);
}

void			show_alloc_mem(void)
{
	extern t_env	g_env;
	int				total;

	total = print_zone("TINY", &(g_env.tiny));
	total += print_zone("SMALL", &(g_env.tiny));
	total += print_zone("LARGE", &(g_env.tiny));
	ft_putstr("Total : ");
	ft_putnbr(total);
	ft_putstr(" octets\n");
}
