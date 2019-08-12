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
	char *str, *ptr;
	if (!(str = malloc(0)))
		return 0;
	printf("Malloc OK\n");
	if (!(ptr = realloc(str, 0)))
		return 0;
	printf("Realloc OK\n");
}
