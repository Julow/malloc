/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/19 21:25:57 by jaguillo          #+#    #+#             */
/*   Updated: 2015/01/19 23:41:09 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include "stdlib.h"

# define TINY_MIN		(1)
# define TINY_MAX		(128)
# define TINY_SIZE		((TINY_MAX + sizeof(t_malloc) + 1) * 100)

# define SMALL_MIN		(TINY_MIN + 1)
# define SMALL_MAX		(16000)
# define SMALL_SIZE		((SMALL_MAX + sizeof(t_malloc) + 1) * 100)

# define LARGE_MIN		(SMALL_MAX + 1)

/*
** 'ptr' the malloc
** 'length' the size of the malloc + sizeof(t_malloc)
** 'next' the next malloc
*/
typedef struct	s_malloc
{
	void			*ptr;
	size_t			length;
	struct s_malloc	*next;
}				t_malloc;

typedef struct	s_zone
{
	void			*min;
	void			*max;
	t_malloc		*first;
}				t_zone;

typedef struct	s_env
{
	t_zone			tiny;
	t_zone			small;
	t_malloc		*large;
}				t_env;

t_env			g_env = {
	(t_zone){NULL, NULL, NULL},
	(t_zone){NULL, NULL, NULL},
	NULL
};

#endif
