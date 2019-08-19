/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbernier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 14:53:47 by pbernier          #+#    #+#             */
/*   Updated: 2019/08/12 14:53:48 by pbernier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "includes/malloc.h"
#include <limits.h>

int main()
{
	char *ptr1;
	char *ptr2;
	char *ptr3;
	char *ptr4;

	ptr1 = NULL;
	ptr2 = NULL;
	ptr3 = NULL;
	ptr4 = NULL;


	ptr1 = malloc(4);
	ptr1[0] = 'A';
	ptr2 = malloc(400);
	ptr2[0] = 'B';
	ptr3 = malloc(40);
	ptr3[0] = 'C';


	ptr1 = realloc(ptr1, 100);

	show_dump_mem(G_TINY);
	show_dump_mem(ptr1);
	// show_dump_mem(ptr2);
	// show_dump_mem(ptr3);
	// show_dump_mem(ptr4);

	show_alloc_mem();
	return (0);

	ptr1 = malloc(13);
	ptr1[0] = 'A';
	printf("-----\n");
	ptr2 = malloc(1);
	ptr2[0] = 'B';
	printf("-----\n");
	ptr3 = malloc(14);
	ptr3[0] = 'C';
	printf("-----\n");

	free(ptr2);
	printf("-----\n");
	ptr4 = malloc(55);
	ptr4[0] = 'D';
	printf("-----\n");

	int i = 0;

	while (i++ < 1000)
	{
		//printf("NB TINY = %f - ", T_NB_BLOC);
		//printf("%d\n", i);
		//if (i == 200)
		//{
			//show_dump_mem(ptr1);
			//show_alloc_mem();
		//}
		(void)malloc(tiny - 1);
	}
	show_dump_mem(ptr1);
	show_dump_mem(ptr2);
	show_dump_mem(ptr3);
	show_dump_mem(ptr4);
	//show_alloc_mem();
	return (0);

	printf("[%zu]\n", ((t_bloc*)ptr2)->size);
	show_dump_mem(ptr2);
	return(0);
}
