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
	//void *ptr;
	//t_bloc	*ptr;
	//void	*cul;

	//ptr = malloc(10);
	//malloc(50);
	//malloc(52);
	malloc(666);
	malloc(1);
	malloc(100);
	malloc(666);
	malloc(16);
	//malloc(555);
	//malloc(444);
	show_alloc_mem();

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
