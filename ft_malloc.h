/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/09 16:18:39 by jaguillo          #+#    #+#             */
/*   Updated: 2015/02/10 15:36:27 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <stddef.h>

# define TINY_MIN			(1)
# define TINY_MAX			(192 + sizeof(t_alloc))
# define TINY_CHUNK			(4096)

# define SMALL_MIN			(TINY_MIN + 1)
# define SMALL_MAX			(TINY_CHUNK * 2 + sizeof(t_alloc))
# define SMALL_CHUNK		(TINY_CHUNK * 8)

# define LARGE_MIN			(SMALL_MAX + 1)
# define LARGE_MAX			((unsigned int)-1)
# define LARGE_CHUNK		(0)

# define ZONE_COUNT			(3)

# define MAX_SIZE			(4294967296 - sizeof(t_alloc) - sizeof(t_chunk) - 4)

/*
** libft?
** # define ARRAY(l,v)			{[0 ... ((l) - 1)] = v}
*/

# define MASK(f,m)			((m) == ((f) & (m)))
# define ISBIT(f,b)			(((f) & (1 << (b))) != 0)
# define BIT(b)				(1 << (b))

# define V(p)				((void*)(p))

/*
** Before each allocs
** size is a multiple of 4 and assume the size of the struct
*/
typedef struct	s_alloc
{
	size_t			size;
	size_t			prev;
	size_t			next;
}				t_alloc;

# define NEXT_ALLOC(a)		((t_alloc)(V(a) + (a)->next))
# define PREV_ALLOC(a)		((t_alloc)(V(a) - (a)->prev))

/*
** Before each chunk
** size does not assume the size of the struct
*/
typedef struct	s_chunk
{
	void			*start;
	size_t			size;
	size_t			free;
	t_alloc			*first;
	struct s_chunk	*next;
}				t_chunk;

/*
** Before each zone
*/
typedef struct	s_zone
{
	int				nothing;
	size_t			min;
	size_t			max;
	size_t			chunk_size;
	t_chunk			*chunk;
}				t_zone;

typedef struct	s_env
{
	t_zone			zone[ZONE_COUNT];
}				t_env;

typedef struct	s_freed
{
	t_alloc			*alloc;
	t_chunk			*chunk;
	t_zone			*zone;
}				t_freed;

void			search_freed(t_freed *res, size_t size);

void			*malloc(size_t size);
void			free(void *ptr);
void			*realloc(void *ptr, size_t size);
void			show_alloc_mem(void);

#endif
