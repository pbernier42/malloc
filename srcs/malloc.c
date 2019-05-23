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
//opt header
//gerer 0
void		*malloc(size_t size)
{
	t_bloc	**page;
	size_t	type;
	void	*ret;

	if (!(page = ((t_bloc**[4]){
		NULL, &g_mem.tiny, &g_mem.small, &g_mem.large})[finder(size, ITER)]))
		return (NULL);
	type = finder(size, TYPE);
	while (!(ret = create_bloc(size, *page, type)))
		if ((!(*page) || !ret) && !new_page(size, page, type))
			return (NULL);
	return (ret);
}

bool		new_page(size_t size, t_bloc **page, size_t type)
{
	t_bloc	*prev;
	t_bloc	*start;
	size_t	s_page;
//pas revenir au debut si c'est un large
	(void)type;
	s_page = finder(size, PAGE);
	prev = NULL;
	start = (*page);
	while ((*page) && (prev = (*page)))
	{
		(*page) = (*page)->next;
	//	printf("[%p]\n", (*page));
	}
	if ((((*page) = mmap(0, s_page, FL_PROT, FL_MAP, -1, 0)) == MAP_FAILED))
		return (false);
	if (((*page)->prev = prev))
		prev->next = (*page);

	(*page)->next = NULL;
	(*page)->size = s_page; //strat de l'infini en bas // si c'est un large il faut faire une boucle
	(*page)->empty = true;

	//printf("{%p}\n\n", (*page));
	if (start)
		(*page) = start;
	return (true);
}

void		*create_bloc(size_t size, t_bloc *page, size_t type)
{
	t_bloc	*better;

	better = NULL;
	if (!page || (type == LARGE && !page->empty) ||
		(type != LARGE && !(better = find_best(size, page,
		(finder(size, PAGE) - finder(size, ZERO)), finder(size, BLOC)))))
		return (NULL);
	else if (type == LARGE && page->empty)
		better = page;
	place_header(size, better, type);
	return (BETTER + SIZE_HEAD);
}

t_bloc		*find_best(size_t size, t_bloc *page, size_t s_page, size_t s_min)
{
	t_bloc	*better;
	void	*cursor;
	size_t	parsed;

	better = NULL;
	while (page && (!better || (better && better->size != size)))
	{
		cursor = page;
		parsed = 0;
		while (parsed < s_page)
		{
			if ((CURSOR->empty) && (CURSOR->size == size ||
				CURSOR->size >= size + SIZE_HEAD + s_min) && (!better ||
				(better && (better->size < CURSOR->size ||
				CURSOR->size == size))))
				better = CURSOR;
			parsed += CURSOR->size + SIZE_HEAD;
			cursor += CURSOR->size + SIZE_HEAD;
		}
		//printf("(%p)\n", page);
		page = page->next;
	}
	return (better);
}

void	place_header(size_t size, t_bloc *better, size_t type)
{
	t_bloc	*next;

	better->empty = false;
	if (type == LARGE || better->size == size)
		return ;
	next = (BETTER + (SIZE_HEAD + size));
	*next = ((t_bloc){better->size - SIZE_HEAD + size, true, NULL, NULL});
	*better = ((t_bloc){size, false, NULL, NULL});
}
