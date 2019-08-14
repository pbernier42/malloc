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

	ptr1 = malloc(13);
	ptr2 = malloc(1);
	ptr3 = malloc(14);
	free(ptr2);
	ptr4 = malloc(9);

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
