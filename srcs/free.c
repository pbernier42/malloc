/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbernier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 14:43:26 by pbernier          #+#    #+#             */
/*   Updated: 2019/05/31 18:49:33 by rlecart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

t_type		g_mem;

void		free(void *ptr)
{
	void			*prev;
	size_t			s_prev;
	t_posi			posi;

	if (!ptr)
		return ;
	posi = check_ptr(ptr, ft_free);
	if (!P_BLOC || !P_PAGE || P_BLOC->empty)
	{
		G_FONCTION = ft_null;
		return ;
	}
	if (HISTORY)
	{
		prev = BLOC + SIZE_HEAD;
		s_prev = P_BLOC->size;
	}
	if (!(delete_bloc(posi, TYPE(P_BLOC->size))))
	{
		G_FONCTION = ft_null;
		return ;
	}
	add_histo((t_hist){true, ft_free, {prev, NULL}, {s_prev, 0}});
}

bool		delete_bloc(t_posi posi, enum e_type type)
{
	void		*cursor;
	size_t		p_size;
	size_t		p_limit[2];
	size_t		as_cur;

	cursor = P_PAGE;
	P_BLOC->empty = true;
	p_size = S_PAGE(P_BLOC->size);
	PAGE_END = (size_t)P_PAGE + p_size;
	while (type != large && (CURS_START = (size_t)cursor) < PAGE_END)
	{
		as_cur = A_SIZE(CURSOR->size);
		if (CURSOR->empty && (CURS_START + SIZE_HEAD + as_cur) < PAGE_END
			&& NEXT_BLOC->empty)
			CURSOR->size = as_cur + SIZE_HEAD + A_SIZE(NEXT_BLOC->size);
		else
			cursor += as_cur + SIZE_HEAD;
	}
	if (type == large || (type != large && P_PAGE->empty
		&& (A_SIZE(P_PAGE->size) == (p_size - SIZE_HEAD))))
		return (delete_page(P_PAGE, p_size, type));
	return (true);
}

bool		delete_page(t_bloc *page, size_t p_size, enum e_type type)
{
	size_t	i;
	t_bloc	*save;

	i = ITERATOR(type);
	save = NULL;
	if (page->prev && page->prev != page)
		page->prev->next = page->next;
	if (page->next && page->next != page)
		page->next->prev = page->prev;
	if (!(page == page->next && page == page->prev))
	{
		save = (page->next) ? page->next : page->prev;
		if (page->next)
			page->next->prev = page->prev;
		else if (page->prev && type != large)
			page->prev->next = NULL;
	}
	if (!save_buff(page, i, p_size, type))
		if (munmap(page, p_size) != 0)
			return (ft_error(munmap_fail));
	if (page == LIST[i])
		*G_LIST[i] = save;
	return (true);
}

bool		save_buff(t_bloc *page, size_t i, size_t p_size, enum e_type type)
{
	size_t	b_size;

	if (G_BUFF[i] && type != large)
		return (false);
	if (G_BUFF[i] && type == large)
	{
		b_size = S_PAGE(G_BUFF[i]->size);
		if (b_size < p_size)
		{
			if (munmap(G_BUFF[i], b_size) != 0)
				return (ft_error(munmap_fail));
		}
		else
			return (false);
	}
	G_BUFF[i] = page;
	return (true);
}

t_bloc		*get_buff(size_t s_page, enum e_type type)
{
	size_t	i;
	size_t	align[2];
	void	*ret;

	i = ITERATOR(type);
	if ((ret = G_BUFF[i]))
	{
		if (type == large)
		{
			AS_NEW = s_page;
			AS_OLD = S_PAGE(G_BUFF[i]->size);
			if (AS_OLD < AS_NEW)
				return (NULL);
			if (AS_OLD > AS_NEW)
			{
				if (munmap(ret + AS_NEW, AS_OLD - AS_NEW) == MUNMAP_FAIL)
					return (ft_error(munmap_fail));
			}
		}
		G_BUFF[i] = NULL;
	}
	return (ret);
}
