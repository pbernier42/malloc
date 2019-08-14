/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmpfree.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbernier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 17:42:35 by pbernier          #+#    #+#             */
/*   Updated: 2019/08/12 17:42:37 by pbernier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <limits.h>

# define FL_PROT			PROT_READ | PROT_WRITE
# define FL_MAP				MAP_ANON | MAP_PRIVATE
# define GPS				getpagesize()

void 	*error(char *error)
{
	write(1, error, 7);
	return (NULL);
}

int		main()
{
	char 	*ptr;
	int		i;

	i = 0;

	while (i++ < 500)
	{
		//ptr = NULL;
		if (((ptr = mmap(NULL, getpagesize(), FL_PROT, FL_MAP, -1, 0)) == MAP_FAILED))
		 	error("FAIL M\n");
		//printf("addr = %zu\n", (size_t)ptr % getpagesize());
		ptr[0] = 42;
		if (munmap(ptr, getpagesize()) != 0)
			error("FAIL F\n");
		printf("%p\n", ptr);
		ptr = NULL;

	}
	return (1);
}

// char	*m_tmp(void)
// {
// 	char *new;
//
// 	if (((new = mmap(0, SIZE, FL_PROT, FL_MAP, -1, 0)) == MAP_FAILED))
// 	 	return (error("FAIL M\n"));
// 	new[0] = 42;
// 	//printf("M = %p\n", new);
// 	return (new);
// }
//
// void 	f_tmp(char *ptr)
// {
// 	//printf("F = %p\n", ptr);
// 	if (munmap(ptr, SIZE) != 0)
// 	 	error("FAIL F\n");
// }
