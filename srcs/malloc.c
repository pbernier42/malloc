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
	t_bloc	**page; //J'ai preferere faire un *page qui prend soit tiny soit small soit large pour le balader partout plutot que de devoir faire des calculs du style "size <= TINY ? TINY : SMALL" a chaque fois que tu veux savoir quoi genre c'est relou
	// Et ** de la meme maniere que GNL avec **line (&str), tqt la syntaxe c'est de l'eau : (*page)->variable; CA VAAAAAAA

	if (size == 0 || size >= LARGE)
		return (NULL);
	page = (size > 0 && size <= TINY ? &g_mem.tiny : &g_mem.small);
	page = (size > SMALL + 1 && size <= LARGE ? &g_mem.large : page);
	if (!(*page) && !new_page(size, page))
		return (NULL);
	return (create_bloc(size, page));
}

bool		new_page(size_t size, t_bloc **page)
{
	t_bloc	*prev;

	prev = *page;
	while (*page)
		if (((*page) = (*page)->next))
			prev = prev->next;

	if (((*page = mmap(0, size == TINY ? TINY : SMALL, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED))
		return (false); // Il faut gerer le cas LARGE

	if (prev)
		prev->next = *page;
	(*page)->prev = prev ? prev : NULL;
	(*page)->next = NULL;
	(*page)->size = type_finder(size);
	(*page)->empty = true;
	return (true);
	// Est-ce qu'il faudrait pas faire g.tiny || g.small || g.large = page pour set les variables "tiny", "small" et "large" dans la structure ?
	// J'ai resolu ca en faisant **page
}

void	*ft_memcpya(void *dst, const void *src, size_t n)
{
	char	*c1;
	char	*c2;

	if (n == 0 || dst == src)
		return (dst);
	c1 = (char*)dst;
	c2 = (char*)src;
	while (--n)
		*c1++ = *c2++;
	*c1 = *c2;
	return (dst);
}

t_bloc		new_bloc(size_t size, bool empty, t_bloc *prev, t_bloc *next)
{
	t_bloc	ret;

	ret.size = size;
	ret.empty = empty;
	ret.prev = prev;
	ret.next = next;
	return (ret);
}

void		*create_bloc(size_t size, t_bloc **page) // Vu qu'on met deux headers (celui demandee et celui d'apres avec la taille qui reste), il y aura toujours un header (un bloc je veux dire, dans le sens ou il y aura le header + la size en question (le reste))
{
	t_bloc	cpy;
	t_bloc	*cursor;

	cursor = *page;
	while (!cursor->empty)// && ca depasse pas la taille max de la page) cursor - page <= type_finder(size)
	{
		cursor += SIZE_HEAD + cursor->size;
	}
	cpy = new_bloc(size, false, size > SMALL /*&& quil y a un elem avant */? /* prev */ NULL : NULL, /* next */ NULL);
	ft_memcpya((void*)cursor, &cpy, SIZE_HEAD);
	return (cursor + SIZE_HEAD + 1);
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
