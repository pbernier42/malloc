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
		if ((!(*page) || !ret) && !new_page(size, S_PAGE(size), page, type))
			return (NULL);
	if (G_FONCTION != ft_realloc)
		add_histo((t_hist){true, ft_malloc, {ret, NULL}, {size, 0}});
	return (ret);
}

bool		new_page(size_t size, size_t s_page, t_bloc **page,
				enum e_type type)
{
	t_bloc	*start;
	t_bloc	*new;

	printf("????\n");
	start = *page;
	while (type != large && (*page) && (*page)->next)
		(*page) = (*page)->next;
	if (((new = mmap(0, s_page, FL_PROT, FL_MAP, -1, 0)) == MAP_FAILED))
		return (false);
	if (type == large && !(*page))
		*new = ((t_bloc){size, true, new, new});
	else if (type == large && (*page))
	{
		*new = ((t_bloc){size, true, (*page), (*page)->next});
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
	t_posi	posi;

	if (!page || (type == large && !page->empty))
		return (NULL);
	posi = (type != large) ?
		find_best(size, page, S_PAGE(size), A_SIZE(S_BLOC_MIN(size))) :
		(t_posi){page, page};
	if (!P_PAGE || !P_BLOC)
		return (NULL);

	place_header(size, posi, type, ft_malloc);

	return (BLOC + SIZE_HEAD);
}

t_posi		find_best(size_t size, t_bloc *page, size_t s_page, size_t as_min)
{
	size_t	align[3];
	t_posi	posi;
	void	*cursor;

	posi = P_NULL;
	AS_NEW = A_SIZE(size);
	while (page && (!P_BLOC || (P_BLOC && AS_BET == AS_NEW)))
	{
		cursor = page;
		while ((size_t)cursor < (size_t)page + s_page)
		{
			AS_CUR = A_SIZE(CURSOR->size);
			if ((CURSOR->empty)
				&& (AS_CUR == AS_NEW || AS_CUR > AS_NEW + SIZE_HEAD + as_min)
				&& (!P_BLOC ||
					(P_BLOC && !(AS_BET == AS_NEW) && (AZ_BET > AZ_CUR))))
			{
				posi = (t_posi){page, CURSOR};
				AS_BET = A_SIZE(P_BLOC->size);
			}
			cursor += AS_CUR + SIZE_HEAD;
		}
		page = page->next;
	}
	return (posi);
}

void		place_header(size_t size, t_posi posi, enum e_type type,
				enum e_fonction fonction)
{
	size_t	align[3];
	size_t	s_page;

	P_BLOC->empty = false;
	if (type == large || P_BLOC->size == size)
	{
		P_BLOC->size = size;
		return ;
	}
	AS_NEW = A_SIZE(size);
	AS_BET = A_SIZE(P_BLOC->size);
	s_page = S_PAGE(size);
	if (((size_t)PAGE + s_page > ((size_t)BLOC + AS_NEW + SIZE_HEAD) &&
		((size_t)PAGE + s_page - ((size_t)BLOC + AS_NEW + SIZE_HEAD) > A_SIZE(S_BLOC_MIN(type)) + SIZE_HEAD)) &&
		(AS_NEW != AS_BET))
	{
		((t_bloc*)(BLOC + (SIZE_HEAD + AS_NEW)))->size = (AS_BET - SIZE_HEAD - AS_NEW);
		((t_bloc*)(BLOC + (SIZE_HEAD + AS_NEW)))->empty = true;
		(void)fonction;
	}
	P_BLOC->size = size;
}
