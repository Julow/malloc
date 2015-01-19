/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/19 21:25:57 by jaguillo          #+#    #+#             */
/*   Updated: 2015/01/19 21:31:01 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include "stdlib.h"

# define TINY_MIN		(1)
# define TINY_MAX		(128)
# define TINY_SIZE		((TINY_MAX + 1) * 100)

# define SMALL_MIN		(TINY_MIN + 1)
# define SMALL_MAX		(32000)
# define SMALL_SIZE		((SMALL_MAX + 1) * 100)

# define LARGE_MIN		(SMALL_MAX + 1)

#endif
