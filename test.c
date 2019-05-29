/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbernier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 17:30:39 by pbernier          #+#    #+#             */
/*   Updated: 2019/05/06 17:30:40 by pbernier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <malloc.h>

int main(void)
{
	int i;
	float a;
	float tmp;
	//void *ptr;
	//t_bloc	*ptr;
	//void	*cul;

	//ptr = malloc(10);
	//malloc(50);
	//malloc(52);

	// i = 9;
	// while (++i < 500)
	// {
	// 	a = (float)(T_SIZE_PAGE / ((float)i + SIZE_HEAD));
	// 	printf("[%d] / ([%d] + [%lu])  => [%f]\n", T_SIZE_PAGE, i, SIZE_HEAD, a);
	// 	tmp = (a * 1000000);
	// 	if (((size_t)tmp % 1000000) == 0)
	// 	{
	// 		printf("[%f] - {{%zu}}\n", T_NB_BLOC, (size_t)a);
	// 	}
	// }

	// malloc(170);
	// malloc(200);
	// malloc(4);
	// malloc(5);
	// malloc(400);
	// malloc(20);
	 // -------------malloc(UINT_MAX + 44);
	// malloc(30);
	// malloc(40);
	// malloc(3);
	// malloc(300);
	// malloc(1);
	//  malloc(200);
	// malloc(2);
	//malloc(17);
	// show_alloc_mem();
	//show_alloc_mem();
	//malloc(555);
	//malloc(444);


	// ptr = mmap(0, 1000, FL_PROT, FL_MAP, -1, 0);
	// cul = (void*)ptr;
	// printf("[%p]\n", ptr);
	// printf("[%p]\n", cul+1);
	//printf("[%p]\n", (char*)ptr + 1);
	//printf("%lu\n", sizeof(t_bloc));
	i = 12;
	//print_define();

	//printf("\nret : {%lu}\n\n", finder(i, PAGE));
	//printf("\nret : {%lu}\n\n", finder(i, TYPE));
	//printf("\nret : {%lu}\n\n", finder(i, ZERO));
	///ptr = malloc(1554560);
	//printf("[%d]\n", getrlimit(-1, ptr));
	//printf("[%d]\n", getpagesize());
	//printf("\n");
	//printf("[%s]\n", (char *)ptr);
	//printf("[%p]\n", ptr);
	//printf("[%c]\n", (char)ptr);
	//free(ptr);

	return (0);
}
