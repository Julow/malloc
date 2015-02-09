/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/09 16:18:39 by jaguillo          #+#    #+#             */
/*   Updated: 2015/02/09 23:00:46 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <stddef.h>

# define TINY_MIN			(1)
# define TINY_MAX			(192 + sizeof(t_alloc))
# define TINY_CHUNK			(4096)

# define SMALL_MIN			(TINY_MIN + 1)
# define SMALL_MAX			(8192 + sizeof(t_alloc))
# define SMALL_CHUNK		(TINY_CHUNK * 8)

# define LARGE_MIN			(SMALL_MAX + 1)
# define LARGE_MAX			((unsigned int)-1)
# define LARGE_CHUNK		(SMALL_CHUNK * 2)

/*
** libft?
** # define ARRAY(l,v)			{[0 ... ((l) - 1)] = v}
*/

typedef struct	s_alloc
{
	int				nothing;
	size_t			size;
	struct s_alloc	*next;
}				t_alloc;

typedef struct	s_chunk
{
	void			*start;
	size_t			size;
	size_t			free;
	t_alloc			*first;
	struct s_chunk	*next;
}				t_chunk;

typedef struct	s_zone
{
	size_t			min;
	size_t			max;
	size_t			chunk_size;
	t_chunk			*chunk;
}				t_zone;

typedef struct	s_env
{
	t_zone			tiny;
	t_zone			small;
	t_zone			large;
}				t_env;

void			*malloc(size_t size);
void			free(void *ptr);
void			*realloc(void *ptr, size_t size);
void			show_alloc_mem(void);

#endif
