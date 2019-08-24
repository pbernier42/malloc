/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbernier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 13:33:51 by pbernier          #+#    #+#             */
/*   Updated: 2019/07/15 13:33:54 by pbernier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

t_type		g_mem;

t_posi		check_ptr(void *ptr, enum e_fonction fonction)
{
	size_t			i;
	t_posi			posi;
	t_bloc			**list;
	enum e_type		type;

	i = 0;
	G_FONCTION = fonction;
	while (i < 3)
	{
		list = G_LIST[i];
		type = ((enum e_type[3]){tiny, small, large})[i++];
		posi = check_list(ptr, *list, type);
		if (P_BLOC && P_PAGE)
			return (posi);
	}
	ft_error(ptr_invalid);
	G_FONCTION = ft_null;
	return (P_NULL);
}

t_posi		check_list(void *ptr, t_bloc *page, enum e_type type)
{
	size_t	p_limit[2];
	size_t	p_size;
	t_bloc	*bloc;

	PAGE_START = 0;
	PAGE_END = 0;
	while (page)
	{
		if (!check_corrupt(page, true, type))
			return (P_NULL);
		if ((PAGE_START == 0 || PAGE_END == 0) || type == large)
			p_size = S_PAGE(page->size);
		PAGE_START = (size_t)page;
		PAGE_END = (size_t)page + p_size;
		if (PAGE_START <= (size_t)ptr && PAGE_END >= (size_t)ptr)
		{
			return (!(bloc = check_page(ptr, page, p_size, type)) ?
				P_NULL : (t_posi){page, bloc});
		}
		if (type == large && page->next == G_LARGE)
			return (P_NULL);
		else
			page = page->next;
	}
	return (P_NULL);
}

void		*check_page(void *ptr, t_bloc *page, size_t p_size,
		enum e_type type)
{
	size_t	b_limit[2];
	void	*cursor;
	size_t	i;
	size_t	align[1];

	if (type == large)
		return (page);
	cursor = page;
	i = ITERATOR(type);
	while ((size_t)cursor < ((size_t)page + p_size))
	{
		if (cursor != page)
			check_corrupt(CURSOR, false, type);
		AS_CUR = (type != large) ? A_SIZE(CURSOR->size) : (p_size - SIZE_HEAD);
		BLOC_START = (size_t)cursor;
		BLOC_END = (size_t)cursor + AS_CUR + SIZE_HEAD;
		if (BLOC_START <= (size_t)ptr && BLOC_END >= (size_t)ptr)
		{
			if (!(type != large && CURSOR->empty) || G_FONCTION != ft_realloc)
				return (cursor);
			return (ft_error(empty_tiny + (i - 1)));
		}
		cursor += AS_CUR + SIZE_HEAD;
	}
	return (ft_error(bloc_not_found));
}

bool		check_corrupt(t_bloc *ptr, bool page, enum e_type type)
{
	size_t			i;
	enum e_error	corrupt;

	i = ITERATOR(type);
	if (((size_t)ptr % A_NB) != 0)
		return (ft_error(((page) ? page_align_tiny : bloc_align_tiny) + i - 1));
	corrupt = corrupt_start;
	if (!ptr->size
		|| (!ptr->empty
			&& ((type == tiny && (ptr->size > tiny))
			|| (type == small && (ptr->size <= tiny || ptr->size > small))
			|| (type == large && (ptr->size <= small || ptr->size > large))))
		|| (ptr->empty && (ptr->size > S_PAGE(type) - SIZE_HEAD)))
		return (ft_error((page) ? corrupt + i : corrupt + i + 3));
	if (page && type != large && (ptr != LIST[i - 1] && !LIST[i - 1]->next))
		return (ft_error(corrupt + i + 6));
	if (type == large && (!ptr->prev || !ptr->next))
		return (ft_error(corrupt + 9));
	return (true);
}
