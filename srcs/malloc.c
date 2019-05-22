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
	if (start)
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
	t_bloc	*better;
	size_t	size_page;
	size_t	parsed;

	start = (*page);
	better = NULL;
	size_page = finder(size, PAGE) - finder(size, ZERO);
	while ((*page) && )
	{
		cursor = page;
		parsed = 0;
		while (parsed < size_page)
		{
			if (((t_bloc*)cursor)->empty &&
				(((t_bloc*)cursor)->size == ))


			parsed += ((t_bloc*)cursor)->size + SIZE_HEAD;

			//CONTINUE
		}
		(*page) = (*page)->next;
	}
	(*page) = start;
	return (NULL);
}

// tmp = map(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
