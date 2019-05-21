/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbernier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 14:43:20 by pbernier          #+#    #+#             */
/*   Updated: 2019/05/17 23:41:49 by rlecart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

t_type		g_mem;

void		*malloc(size_t size)
{
	t_bloc	**page;

	if (size == 0 || size >= LARGE)
		return (NULL);
	page = (size > 0 && size <= TINY ? &g_mem.tiny : &g_mem.small);
	page = (size > SMALL && size <= LARGE ? &g_mem.large : page);
	if (!(*page) && !new_page(size, page))
		return (NULL);
	return (create_bloc(size, page));
}

bool		new_page(size_t size, t_bloc **page)
{
	t_bloc	*prev;
	t_bloc	*start;
	size_t	size_page;

	size_page = finder(size, PAGE);
	prev = NULL;
	start = (*page);
	while ((*page) && (prev = (*page)))
		(*page) = (*page)->next;
	if ((((*page) = mmap(0, size_page, FL_PROT, FL_MAP, -1, 0)) == MAP_FAILED))
		return (false);
	(*page)->prev = prev;
	(*page)->next = NULL;
	(*page)->size = size_page - SIZE_HEAD;
	(*page)->empty = true;
	(*page) = start;
	return (true);
}

// void	*ft_memcpya(void *dst, const void *src, size_t n)
// {
// 	char	*c1;
// 	char	*c2;
//
// 	if (n == 0 || dst == src)
// 		return (dst);
// 	c1 = (char*)dst;
// 	c2 = (char*)src;
// 	while (--n)
// 		*c1++ = *c2++;
// 	*c1 = *c2;
// 	return (dst);
// }

// t_bloc		new_bloc(size_t size, bool empty, t_bloc *prev, t_bloc *next)
// {
// 	t_bloc	ret;
//
// 	ret.size = size;
// 	ret.empty = empty;
// 	ret.prev = prev;
// 	ret.next = next;
// 	return (ret);
// }

void		*create_bloc(size_t size, t_bloc **page) // Vu qu'on met deux headers (celui demandee et celui d'apres avec la taille qui reste), il y aura toujours un header (un bloc je veux dire, dans le sens ou il y aura le header + la size en question (le reste))
{
	t_bloc	*start;
	void	*cursor;
	t_bloc	*bigger;
	size_t	size_page;
	size_t	parsed;

	start = (*page);
	bigger = NULL;
	size_page = finder(size, PAGE); - //ZERO
	parsed = 0;
	while ((*page))
	{
		cursor = (*start);
		while (parsed < size_page)
		{
			parsed += (t_bloc)cursor.size + SIZE_HEAD;
			//CONTINUE
		}
		(*page) = (*page)->next;

	}
	(*page) = start;
	// cpy = new_bloc(size, false, size > SMALL /*&& quil y a un elem avant */? /* prev */ NULL : NULL, /* next */ NULL);
	// ft_memcpya((void*)cursor, &cpy, SIZE_HEAD);
	return (NULL);
	// cursor = new_bloc(size, empty, prev, next);
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
