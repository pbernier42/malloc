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
#include <unistd.h>
#include <string.h>
#define M (1024 * 1024)

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

	ptr2 = malloc(58888);
	ptr2[0] = '1';
	free(ptr2);
	//printf("1 = %p\n", G_LARGE);
	// printf("1 = %p\n", G_BUFF[2]);
	// printf("1 = (%zu)\n\n", G_LARGE->size);

	// printf("1 = %p\n", G_LARGE);
	// printf("1 = %p\n", G_BUFF[2]);
	// printf("1 = (%zu)\n\n", G_BUFF[2]->size);


	ptr1 = malloc(80000);
	ptr1[0] = '2';
	free (ptr1);

	// printf("2 = %p\n", G_LARGE);
	// printf("  = %p\n  = %p\n", G_LARGE->prev, G_LARGE->next);
	// printf("2 = (%zu)\n", G_LARGE->size);

	// printf("2 = %p\n", G_BUFF[2]);
	// printf("2 = (%zu)\n", G_BUFF[2]->size);
	// printf("[%c] [%c]\n\n", ptr1[0], ((char*)((((char*)G_LARGE) + 32)))[0]);


	// printf("[%c] [%c]\n\n", ptr1[0], ((char*)((((char*)G_BUFF[2]) + 32)))[0]);


	// printf("[%c] [%c]\n\n", ptr1[0], ((char*)((((char*)G_BUFF[2]) + 32)))[0]);

	// printf("\n| = %p\n", G_LARGE);
	// printf("| = (%zu)\n\n", G_LARGE->size);
	// printf("2 = %p\n", G_LARGE->size);

	//free(ptr1);

	return(0);
}
