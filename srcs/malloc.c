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
	void	*ret;

	ret = NULL;
	if (size == 0 || size >= LARGE)
		return (ret);
	//A VOIR
	page = (size > 0 && size <= TINY ? &g_mem.tiny : &g_mem.small);
	page = (size > SMALL && size <= LARGE ? &g_mem.large : page);

	while (!(ret = create_bloc(size, page)))
		if ((!(*page) || !ret) && !new_page(size, page))
			return (NULL);

	return (ret);
}

bool		new_page(size_t size, t_bloc **page)
{
	t_bloc	*prev;
	t_bloc	*start;
	size_t	s_page;

	s_page = finder(size, PAGE);
	prev = NULL;
	start = (*page);
	while ((*page) && (prev = (*page)))
		(*page) = (*page)->next;
	if ((((*page) = mmap(0, s_page, FL_PROT, FL_MAP, -1, 0)) == MAP_FAILED))
		return (false);
	(*page)->prev = prev;
	(*page)->next = NULL;
	(*page)->size = s_page - SIZE_HEAD;
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
	size_t	s_page;
	size_t	parsed;
	size_t	s_min;

	if (!(*page))
		return (NULL);
	start = (*page);
	better = NULL;
	//finder(size, TYPE) == LARGE ? -s_HEAD
	s_page = finder(size, PAGE) - finder(size, ZERO);
	s_min = finder(size, BLOC);
	//si c'est LARGE BEtter = LA FIN LISE CHAINE
	while ((*page) && (!better || (better && better->size != size)))
	{
		cursor = (*page);
		parsed = 0;
		while (parsed < s_page)
		{
			//!(better && better->size == size) &&
			if ((CURSOR->empty) &&
			(CURSOR->size == size || CURSOR->size >= size + SIZE_HEAD + s_min) &&
			(!better || (better && (better->size < CURSOR->size || CURSOR->size == size))))
				better = CURSOR;
			parsed += CURSOR->size + SIZE_HEAD;
			cursor += CURSOR->size + SIZE_HEAD;
		}
		(*page) = (*page)->next;
	}
	(*page) = start;
	if (!better)
		return (NULL);
	if (better->size != size)
	{
		(better + SIZE_HEAD + size)->empty = true;
		(better + SIZE_HEAD + size)->size = better->size - (SIZE_HEAD + size);
	}
	better->empty = false;
	better->size = size;
	return (((void *)better) + SIZE_HEAD);
}

// tmp = map(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
