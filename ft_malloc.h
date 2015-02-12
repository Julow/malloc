/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/09 16:18:39 by jaguillo          #+#    #+#             */
/*   Updated: 2015/02/12 13:48:55 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <stddef.h>

# define TINY_MIN			(1)
# define TINY_MAX			(192)
# define TINY_CHUNK			(4096)

# define SMALL_MIN			(TINY_MIN + 1)
# define SMALL_MAX			(TINY_CHUNK)
# define SMALL_CHUNK		(TINY_CHUNK * 2)

# define LARGE_MIN			(SMALL_MAX + 1)
# define LARGE_MAX			((unsigned int)-1)
# define LARGE_CHUNK		(0)

# define ZONE_COUNT			(3)

# define MAX_SIZE			(4294967296 - sizeof(t_alloc) - sizeof(t_chunk) - 4)

# define MMAP_PROT			PROT_READ | PROT_WRITE
# define MMAP_FLAG			MAP_ANON | MAP_PRIVATE

/*
** libft?
** # define ARRAY(l,v)			{[0 ... ((l) - 1)] = v}
*/
# define MASK(f,m)			((m) == ((f) & (m)))
# define ISBIT(f,b)			(((f) & (1 << (b))) != 0)
# define BIT(b)				(1 << (b))

# define V(p)				((void*)(p))

# define WORD(n)			(((n) + 3) / 4 * 4)

# define TULONG				unsigned long long int
typedef TULONG	t_ulong;
# undef TULONG

/*
** Before each allocs
** size is a multiple of 4 and assume the size of the struct
*/
typedef struct	s_alloc
{
	int				nothing;
	size_t			size;
	size_t			prev;
	size_t			next;
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
	void			*last_map;
	size_t			page_size;
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

int				chunk_search(t_freed *res, size_t size);
void			search_freed(t_freed *res, size_t size);

/*
** free
*/
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
# define DEBUG_FLAGS		BIT(1) // TODO
# define DEBUG_INFO			BIT(2)
# define DEBUG_FREE			(BIT(3) | DEBUG_CHUNK)
# define DEBUG_ALL			(-1)

int				ft_putstr(const char *str);
int				ft_putulong(unsigned long long int n);
int				ft_putexa(unsigned long long int exa);

/*
** utils
*/
size_t			ft_umax(size_t a, size_t b);
size_t			page_round(size_t size);

#endif
