/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbernier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 14:43:20 by pbernier          #+#    #+#             */
/*   Updated: 2019/05/23 22:33:48 by rlecart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

t_type		g_mem;

void		*malloc(size_t size)
{
	t_bloc		**page;
	enum e_type	type;
	void		*ret;

	if (!(page = ((t_bloc**[4]){
		NULL, &G_TINY, &G_SMALL, &G_LARGE})[ITERATOR(size)])
		|| !(type = TYPE(size)))
		return (NULL);
	while (!(ret = create_bloc(size, *page, type)))
		if ((!(*page) || !ret) && !new_page(S_PAGE(size), page, type))
			return (NULL);
	if (g_mem.fonction != ft_realloc)
		add_histo((t_hist){true, ft_malloc, {ret, NULL}, {size, 0}});
	return (ret);
}

bool		new_page(size_t s_page, t_bloc **page, enum e_type type)
{
	t_bloc	*start;
	t_bloc	*new;

	start = *page;
	while (type != large && (*page) && (*page)->next)
		(*page) = (*page)->next;
	if (((new = mmap(0, s_page, FL_PROT, FL_MAP, -1, 0)) == MAP_FAILED))
		return (false);
	if (type == large && !(*page))
		*new = ((t_bloc){s_page - SIZE_HEAD, true, new, new});
	else if (type == large && (*page))
	{
		*new = ((t_bloc){s_page - SIZE_HEAD, true, (*page), (*page)->next});
		(*page)->next->prev = new;
	}
	else if (type != large)
		*new = ((t_bloc){s_page - SIZE_HEAD, true, (*page), NULL});
	if ((*page))
	{
		(*page)->next = new;
		(*page) = (type != large) ? start : (*page)->next;
	}
	else
		(*page) = new;
	return (true);
}

void		*create_bloc(size_t size, t_bloc *page, enum e_type type)
{
	t_bloc	*better;

	better = NULL;
	if (!page || (type == large && !page->empty)
		|| (type != large && !(better = find_best(A_SIZE(size), page,
			S_PAGE(size), S_BLOC_MIN(size)))))
		return (NULL);
	if (type == large && page->empty)
		better = page;
	place_header(size, better, type, ft_malloc);
	return (BETTER + SIZE_HEAD);
}

t_bloc		*find_best(size_t a_new, t_bloc *page, size_t s_page, size_t s_min)
{
	size_t	align;
	t_bloc	*better;
	void	*cursor;
	size_t	parsed;

	better = NULL;
	while (page && (!better || (better && !A_ZERO(better->size))))
	{
		cursor = page;
		parsed = 0;
		while (parsed < s_page)
		{
			AS_C = A_SIZE(CURSOR->size);
			if ((CURSOR->empty)
				&& (AS_C == AS_N || AS_C > AS_N + SIZE_HEAD + A_SIZE(s_min))
				&& (!better || (better
					&& (AS_B < AS_C || (AS_B == AS_C && AZ_B > AZ_C)))))
				better = CURSOR;
			parsed += AS_C + SIZE_HEAD;
			cursor += AS_C + SIZE_HEAD;
		}
		page = page->next;
	}
	return (better);
}

void		place_header(size_t size, t_bloc *better, enum e_type type,
				enum e_fonction fonction)
{
	size_t	a_size;

	better->empty = false;
	if (type == large || better->size == size)
		return ;

	a_size = A_SIZE(size);

	((t_bloc*)(BETTER + (SIZE_HEAD + size)))->size =

	(fonction == ft_realloc) ?
		((t_bloc*)(BETTER + (SIZE_HEAD + better->size)))->size -
			(better->size - size) :
		(better->size - SIZE_HEAD - size);

	((t_bloc*)(BETTER + (SIZE_HEAD + size)))->empty = true;

	better->size = size;
	better->empty = false;
}
