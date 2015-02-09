/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/09 16:18:39 by jaguillo          #+#    #+#             */
/*   Updated: 2015/02/09 18:09:16 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <stddef.h>

# define TINY_MIN			(1)
# define TINY_MAX			(256)

# define SMALL_MIN			(TINY_MIN + 1)
# define SMALL_MAX			(8192)

# define LARGE_MIN			(SMALL_MAX + 1)
# define LARGE_MAX			((unsigned int)-1)

# define CHUNK_PER_ZONE		10

# define ALLOC_PER_CHUNK	10

# define ARRAY(l,v)			{[0 ... ((l) - 1)] = v}

typedef struct	s_alloc
{
	size_t			size;
	void			*ptr;
}				t_alloc;

typedef struct	s_chunk
{
	void			*start;
	size_t			size;
	t_alloc			allocs[ALLOC_PER_CHUNK];
}				t_chunk;

typedef struct	s_zone
{
	size_t			min;
	size_t			max;
	t_chunk			chunks[CHUNK_PER_ZONE];
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
