/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/20 13:29:15 by jaguillo          #+#    #+#             */
/*   Updated: 2015/01/20 18:10:07 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include <unistd.h>

#define PUTNBR_BUFF		41

static int		ft_putstr(char *str)
{
	int				len;

	len = -1;
	while (str[++len] != '\0')
		;
	return (write(1, str, len));
}

static int		ft_putulong(t_ulong n)
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

static int		ft_putexa(t_ulong exa)
{
	const char		*base = "0123456789ABCDEF";
	char			nb[PUTNBR_BUFF];
	size_t			i;

	if (exa == 0)
		return (ft_putstr("EMPTY"));
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

static t_ulong	print_zone(char *name, t_zone *zone)
{
	t_ulong			total;
	t_malloc		*tmp;

	total = 0;
	ft_putstr(name);
	ft_putstr(" : ");
	ft_putexa((t_ulong)(zone->start));
	ft_putstr("\n");
	tmp = zone->first;
	while (tmp != NULL)
	{
		ft_putexa((t_ulong)(START(tmp)));
		ft_putstr(" - ");
		ft_putexa((t_ulong)(tmp + tmp->length));
		ft_putstr(" : ");
		ft_putulong(tmp->length - sizeof(t_malloc));
		ft_putstr(" octets\n");
		total += tmp->length - sizeof(t_malloc);
		tmp = tmp->next;
	}
	return (total);
}

void			show_alloc_mem(void)
{
	extern t_env	g_env;
	t_ulong			total;

	total = print_zone("TINY", &(g_env.tiny));
	total += print_zone("SMALL", &(g_env.small));
	total += print_zone("LARGE", &(g_env.large));
	ft_putstr("Total : ");
	ft_putulong(total);
	ft_putstr(" octets\n");
}
