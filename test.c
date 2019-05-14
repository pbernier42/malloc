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
	void *ptr;

	ptr = malloc(0);
	//ptr = malloc(1554560);
	//printf("[%d]\n", getrlimit(-1, ptr));
	//printf("[%d]\n", getpagesize());
	//printf("\n");
	//printf("[%s]\n", (char *)ptr);
	//printf("[%p]\n", ptr);
	//printf("[%c]\n", (char)ptr);
	//free(ptr);

	return (0);
}
