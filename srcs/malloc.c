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

void		*malloc(size_t size)
{
	if (size == 0 || size > LARGE)
		return (NULL);
	if ((size <= TINY && !g_mem->tiny) ||
		(size > TINY && size <= SMALL && !g_mem->small))
		if (!new_page(size <= TINY ? TINY : SMALL))
			return (NULL);


	return (new_bloc(size));
}

bool	new_page(size_t mem)
{
	t_bloc	*page;
	t_bloc	*prev;

	page = (mem == TINY ? g_mem->tiny : g_mem->small)
	prev = page;
	while (page)
		page = page->next;
	if ((page = mmap(0, mem == TINY ? TINY : SMALL,
		PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0) == MAP_FAILED))
		return (0);
	page->prev = prev;
	page->next = NULL;
	return (1);
}

void	new_bloc(size_t size)
{
	t_bloc	*prev;

	if (size >= SMALL)
	{
		prev = g_mem->large;
		g_mem->large->next =
			map(0, size + SIZE_HEAD,
				PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	}
	return ();
}

// tmp = map(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);



// void 		print_define()
// {
// 	printf("T_SIZE_HEAD	= [%d]\n", SIZE_HEAD);
// 	printf("T_SIZE_DATA	= [%d]\n", T_SIZE_DATA);
// 	printf("T_SIZE_BLOC	= [%d]\n", T_SIZE_BLOC);
// 	printf("T_SIZE_PAGE	= [%d]\n", T_SIZE_PAGE);
// 	printf("T_SIZE_ZERO	= [%d]*\n", T_SIZE_ZERO);
// 	printf("T_NB_BLOC	= [%f] (Min 100)*\n\n", (float)T_NB_BLOC);
//
// 	printf("S_SIZE_HEAD	= [%d]\n", SIZE_HEAD);
// 	printf("S_SIZE_DATA	= [%d]\n", S_SIZE_DATA);
// 	printf("S_SIZE_BLOC	= [%d]\n", S_SIZE_BLOC);
// 	printf("S_SIZE_PAGE	= [%d]\n", S_SIZE_PAGE);
// 	printf("S_SIZE_ZERO	= [%d]*\n", S_SIZE_ZERO);
// 	printf("S_NB_BLOC	= [%f] (Min 100)*\n", (float)S_NB_BLOC);
// }
