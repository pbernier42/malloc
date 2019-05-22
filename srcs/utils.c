/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlecart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 19:57:04 by rlecart           #+#    #+#             */
/*   Updated: 2019/05/17 23:16:13 by rlecart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

size_t		finder(size_t size, int i)
{
	size_t	type;

	type = 0;
	while (size >= ((size_t[4]){0, TINY, SMALL, size})[type]
		&& size < LARGE)
		++type;
	return (((size_t[4]){
		((size_t[4]){0, T_SIZE_PAGE, S_SIZE_PAGE, size + SIZE_HEAD})[type],
		((size_t[4]){0, TINY, SMALL, size})[type],
		((size_t[4]){0, T_SIZE_ZERO, S_SIZE_ZERO, 0})[type],
		((size_t[4]){0, 1, T_SIZE_BLOC + 1, S_SIZE_BLOC + 1})[type]
		})[i]);
}

// void 		print_define()
// {
// 	printf("T_SIZE_HEAD	= [%lu]\n", SIZE_HEAD);
// 	printf("T_SIZE_DATA	= [%d]\n", T_SIZE_DATA);
// 	printf("T_SIZE_BLOC	= [%lu]\n", T_SIZE_BLOC);
// 	printf("T_SIZE_PAGE	= [%d]\n", T_SIZE_PAGE);
// 	printf("T_SIZE_ZERO	= [%lu]*\n", T_SIZE_ZERO);
// 	printf("T_NB_BLOC	= [%f] (Min 100)*\n\n", (float)T_NB_BLOC);
//
// 	printf("S_SIZE_HEAD	= [%lu]\n", SIZE_HEAD);
// 	printf("S_SIZE_DATA	= [%d]\n", S_SIZE_DATA);
// 	printf("S_SIZE_BLOC	= [%lu]\n", S_SIZE_BLOC);
// 	printf("S_SIZE_PAGE	= [%d]\n", S_SIZE_PAGE);
// 	printf("S_SIZE_ZERO	= [%lu]*\n", S_SIZE_ZERO);
// 	printf("S_NB_BLOC	= [%f] (Min 100)*\n", (float)S_NB_BLOC);
// }
