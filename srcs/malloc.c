/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbernier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 14:43:20 by pbernier          #+#    #+#             */
/*   Updated: 2019/05/06 14:43:21 by pbernier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

t_type		g_mem;

void 		print_define()
{
	printf("T_SIZE_HEAD	= [%d]\n", SIZE_HEAD);
	printf("T_SIZE_DATA	= [%d]\n", T_SIZE_DATA);
	printf("T_SIZE_BLOC	= [%d]\n", T_SIZE_BLOC);
	printf("T_SIZE_PAGE	= [%d]\n", T_SIZE_PAGE);
	printf("T_SIZE_ZERO	= [%d]*\n", T_SIZE_ZERO);
	printf("T_NB_BLOC	= [%f] (Min 100)*\n\n", (float)T_NB_BLOC);

	printf("S_SIZE_HEAD	= [%d]\n", SIZE_HEAD);
	printf("S_SIZE_DATA	= [%d]\n", S_SIZE_DATA);
	printf("S_SIZE_BLOC	= [%d]\n", S_SIZE_BLOC);
	printf("S_SIZE_PAGE	= [%d]\n", S_SIZE_PAGE);
	printf("S_SIZE_ZERO	= [%d]*\n", S_SIZE_ZERO);
	printf("S_NB_BLOC	= [%f] (Min 100)*\n", (float)S_NB_BLOC);
}

void		*malloc(size_t size)
{
	if (size == 0 || size > LARGE)
		return (NULL);
	// if (size <= TINY || size <= SMALL)
	// 	if (!pre_alloc(size <= TINY ? TINY : SMALL))
	// 		return (NULL);
	print_define();

	//page / (40 + 16)

	return (NULL);
}

// bool		pre_alloc(t_size mem)
// {
// 	if (mem == TINY && !g_mem.tiny)
// 		if ((g_mem.tiny =
// 			map(0, (HEAD + ), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
// 			return (0);
// 	if (mem == SMALL && !g_mem.small)
//
// }

// tmp = map(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
// printf("[%zu]\n", sizeof(t_bloc));
// printf("[%d - %d]\n", TINY, SMALL);
