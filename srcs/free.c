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
	void			**start;

	start = NULL;
	if (!ptr || !(start = check_ptr(ptr, ft_free))
		|| (start && ((t_bloc*)start[1])->empty))
	{
		if (G_FONCTION == ft_free)
			G_FONCTION = ft_null;
		return ;
	}
	if (HISTORY)
	{
		prev = start[1] + SIZE_HEAD;
		s_prev = ((t_bloc*)start[1])->size;
	}
	if (!(delete_bloc(start[0], start[1])))
	{
		G_FONCTION = ft_null;
		return ;
	}
	add_histo((t_hist){true, ft_free, {prev, NULL}, {s_prev, 0}});
}

bool		delete_bloc(t_bloc *page, t_bloc *bloc)
{
	void		*cursor;
	enum e_type	type;
	size_t		p_size;
	size_t		p_limit[2];
	size_t		align[1];

	//printf("---%p\n", ((void*)bloc) + 32);
	cursor = page;
	type = TYPE(bloc->size);
	bloc->empty = true;
	p_size = S_PAGE(bloc->size);
	PAGE_END = (size_t)page + p_size;
	while (type != large && (CURS_START = (size_t)cursor) < PAGE_END)
	{

		AS_CUR = A_SIZE(CURSOR->size);
		//printf("{%zu}\n\n", AS_CUR);
		if (CURSOR->empty && (CURS_START + SIZE_HEAD + AS_CUR) < PAGE_END
			&& NEXT_BLOC->empty)
			{
		//		printf("Change\n");
				CURSOR->size = AS_CUR + SIZE_HEAD + NEXT_BLOC->size;
			}
		else
		{
		//	printf("GO\n");
			cursor += AS_CUR + SIZE_HEAD;
		}
	}

	if (type == large || (type != large && page->empty
		&& (page->size == (p_size - SIZE_HEAD))))
		return (delete_page(page, p_size, type));
	return (true);
}

bool		delete_page(t_bloc *page, size_t p_size, enum e_type type)
{
	size_t	i;
	t_bloc	*save;

	printf("!!!\n");
	i = ITERATOR(type) - 1;
	if (page->prev && page->prev != page)
		page->prev->next = page->next;
	if (page->next && page->next != page)
		page->next->prev = page->prev;
	if (!(page == page->next && page == page->prev))
		save = (page->next) ? page->next : page->prev;
	else
		save = NULL;
	if (munmap(page, p_size) != 0)
		return (ft_error(munmap_fail));
	if (page == LIST[i])
		*G_LIST[i] = save;
	return (true);
}
