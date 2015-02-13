/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/09 16:18:39 by jaguillo          #+#    #+#             */
/*   Updated: 2015/02/13 18:26:19 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <stddef.h>

# define TINY_MIN			(MIN_SIZE)
# define TINY_MAX			(1024)
# define TINY_CHUNK			(1024 * 32)

# define SMALL_MIN			(TINY_MIN + 1)
# define SMALL_MAX			(1024 * 128)
# define SMALL_CHUNK		(1024 * 1024)

# define LARGE_MIN			(SMALL_MAX + 1)
# define LARGE_MAX			((t_uint)-1)
# define LARGE_CHUNK		(0)

# define ZONE_COUNT			(3)

# define MIN_SIZE			(1)
# define MAX_SIZE			(LARGE_MAX - sizeof(t_alloc) - sizeof(t_chunk) - 8)

# define MMAP_PROT			PROT_READ | PROT_WRITE
# define MMAP_FLAG			MAP_ANON | MAP_PRIVATE

typedef unsigned int			t_uint;

typedef unsigned long long int	t_ulong;

/*
** libft?
** # define ARRAY(l,v)			{[0 ... ((l) - 1)] = v}
*/
# define MASK(f,m)			((m) == ((f) & (m)))
# define ISBIT(f,b)			(((f) & (1 << (b))) != 0)
# define BIT(b)				(1 << (b))

# define V(p)				((void*)(p))

# define WORD(n)			(((n) + 3) / 4 * 4)

/*
** Before each allocs
** flags
**  BIT(0) = free
** size is a multiple of 4 and assume the size of the struct
*/
typedef struct	s_alloc
{
	int				flags;
	t_uint			size;
	t_uint			prev;
	t_uint			next;
}				t_alloc;

# define ALLOC(s,p,n)		((t_alloc){0, (s), (p), (n)})

# define NEXT_ALLOC(a)		((t_alloc*)(V(a) + (a)->next))
# define PREV_ALLOC(a)		((t_alloc*)(V(a) - (a)->prev))
# define INSERT_ALLOC(a)	((t_alloc*)(V(a) + (a)->size))

/*
** Before each chunk
** size does not assume the size of the struct
*/
typedef struct	s_chunk
{
	t_uint			size;
	t_uint			free;
	t_alloc			*first;
	struct s_chunk	*next;
	struct s_chunk	*prev;
}				t_chunk;

# define CHUNK_START(c)		(V(c) + sizeof(t_chunk))

/*
** Before each zone
*/
typedef struct	s_zone
{
	int				nothing;
	t_uint			min;
	t_uint			max;
	t_uint			chunk_size;
	t_chunk			*chunk;
}				t_zone;

typedef struct	s_env
{
	t_zone			zone[ZONE_COUNT];
	void			*last_map;
	t_uint			page_size;
}				t_env;

typedef struct	s_freed
{
	t_alloc			*alloc;
	t_chunk			*chunk;
	t_zone			*zone;
}				t_freed;

/*
** malloc
*/
void			*malloc(size_t size);

int				chunk_search(t_freed *res, t_uint size);
void			search_freed(t_freed *res, t_uint size);

/*
** free
*/
int				search_alloc(t_freed *res, void *ptr);

void			free(void *ptr);

/*
** realloc
*/
void			*realloc(void *ptr, size_t size);

/*
** show_alloc_mem
*/
void			show_alloc_mem(void);
void			show_alloc_debug(int flags);

# define DEBUG_CHUNK		BIT(0)
# define DEBUG_FLAGS		BIT(1)
# define DEBUG_INFO			BIT(2)
# define DEBUG_FREE			(BIT(3) | DEBUG_CHUNK)
# define DEBUG_ALL			(-1)

int				ft_putstr(const char *str);
int				ft_putulong(unsigned long long int n);
int				ft_putexa(unsigned long long int exa);

/*
** utils
*/
t_uint			ft_umax(t_uint a, t_uint b);
t_uint			page_round(t_uint size);

#endif
