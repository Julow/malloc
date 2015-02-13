/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/20 14:42:30 by jaguillo          #+#    #+#             */
/*   Updated: 2015/02/13 18:19:49 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include <string.h>
#include <stdio.h>

#define PRINT(f,...)	printf(f, ##__VA_ARGS__);fflush(stdout)

static void		test_size(int size)
{
	void			*ptr;

	PRINT("malloc (%d)... ", size);
	ptr = malloc(size);
	PRINT("\n");
	PRINT("bzero (%d)... ", size);
	bzero(ptr, size);
	PRINT("\n");
	PRINT("show_alloc_mem...\n");
	show_alloc_mem();
	PRINT("free... ");
	free(ptr);
	PRINT("\n");
}

static void		test_test(void)
{
	void			*ptr;

	if ((malloc(50)) == NULL)
		PRINT("(null)\n");
	if ((malloc(50)) == NULL)
		PRINT("(null)\n");
	if ((ptr = malloc(50)) == NULL)
		PRINT("(null)\n");
	if ((malloc(50)) == NULL)
		PRINT("(null)\n");
	if ((malloc(50)) == NULL)
		PRINT("(null)\n");
	free(ptr);
	if ((malloc(50)) == NULL)
		PRINT("(null)\n");
	if ((malloc(250)) == NULL)
		PRINT("(null)\n");
	if ((malloc(250)) == NULL)
		PRINT("(null)\n");
	if ((ptr = malloc(250)) == NULL)
		PRINT("(null)\n");
	if ((malloc(250)) == NULL)
		PRINT("(null)\n");
	if ((malloc(250)) == NULL)
		PRINT("(null)\n");
	free(ptr);
	if ((malloc(250)) == NULL)
		PRINT("(null)\n");
	show_alloc_debug(DEBUG_ALL);
}

static void		test_null(void)
{
	void			*ptr;

	PRINT("malloc(0)... ");
	if ((ptr = malloc(0)) == NULL)
		PRINT("(null)");
	PRINT("\n");
	PRINT("free(malloc(0))... ");
	ptr = malloc(0);
	free(ptr);
	PRINT("\n");
	PRINT("double free... ");
	free(ptr);
	PRINT("\n");
	PRINT("free(NULL)... ");
	free(NULL);
	PRINT("\n");
}

static void		test_loop(int size, int loop)
{
	void			*ptr;

	if ((malloc(size)) == NULL)
		PRINT("(null)\n");
	if ((malloc(size)) == NULL)
		PRINT("(null)\n");
	if ((malloc(size)) == NULL)
		PRINT("(null)\n");
	if ((malloc(size)) == NULL)
		PRINT("(null)\n");
	PRINT("malloc (%d), free x %d... ", size, loop);
	while (loop > 0)
	{
		ptr = malloc(size);
		bzero(ptr, size);
		free(ptr);
		loop--;
	}
	PRINT("\n");
	show_alloc_debug(DEBUG_ALL);
}

static void		test_show(int size, int loop)
{
	PRINT("malloc (%d) x %d... ", size, loop);
	while (loop > 0)
	{
		if (malloc(size) == NULL)
			printf("\nreturn NULL");
		loop--;
	}
	PRINT("\n");/*
	PRINT("show_alloc_mem...\n");
	show_alloc_mem();*/
}

int				main(int argc, char **argv)
{
	while (argc > 1)
	{
		if (strcmp(argv[1], "size") == 0 && argc > 2)
			test_size(atoi(argv[2]));
		else if (strcmp(argv[1], "loop") == 0 && argc > 3)
			test_loop(atoi(argv[2]), atoi(argv[3]));
		else if (strcmp(argv[1], "show") == 0 && argc > 3)
			test_show(atoi(argv[2]), atoi(argv[3]));
		else if (strcmp(argv[1], "test") == 0)
			test_test();
		else if (strcmp(argv[1], "null") == 0)
			test_null();
		else
			break ;
		return (0);
	}
	PRINT("usage: ./a.out\n");
	PRINT("	size [size]\n");
	PRINT("	loop [size] [loop]\n");
	PRINT("	show [size] [loop]\n");
	PRINT("	test\n");
	PRINT("	null\n");
	return (1);
}
