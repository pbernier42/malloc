/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbernier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 14:43:26 by pbernier          #+#    #+#             */
/*   Updated: 2019/05/31 18:49:33 by rlecart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

bool			delete_page2(t_bloc *page, size_t p_size, enum e_type type);

void			**check_list(void *ptr, t_bloc *page, enum e_type type);
bool			check_corrupt(t_bloc *ptr, bool page, enum e_type type);
void			*check_page(void *ptr, t_bloc *page, size_t p_size, enum e_type type);

#define	LIST		((t_bloc*[3]){G_TINY, G_SMALL, G_LARGE})
#define G_LIST		((t_bloc**[3]){&G_TINY, &G_SMALL, &G_LARGE})
#define PAGE_START	p_limit[0]
#define PAGE_END	p_limit[1]
#define BLOC_START	b_limit[0]
#define BLOC_END	b_limit[1]
#define NEXT_BLOC	((t_bloc*)(cursor + SIZE_HEAD + CURSOR->size))
#define CURS_START	p_limit[0]

void		free2(void *ptr)
{
	void			*prev;
	size_t			s_prev = 0;
	void			**start;

	start = NULL;
	if (!ptr || !(start = check_ptr(ptr, ft_free)) ||
		(start && ((t_bloc*)start[1])->empty))
	{
		if (g_mem.fonction == ft_free)
			g_mem.fonction = ft_null;
		return ;
	}
	if (HISTORY)
	{
		prev = start[1] + SIZE_HEAD;
		s_prev = ((t_bloc*)start[1])->size;
	}
	if (!(delete_bloc(start[0], start[1])))
	{
		g_mem.fonction = ft_null;
		return ;
	}
	add_histo((t_hist){true, ft_free, {prev, NULL}, {s_prev, 0}});
}

bool		delete_bloc(t_bloc *page, t_bloc *bloc)
{
	void 		*cursor;
	enum e_type	type;
	size_t		p_size;
	size_t		p_limit[2];

	cursor = page;
	type = TYPE(bloc->size);
	bloc->empty = true;
	p_size = S_PAGE(bloc->size);
	PAGE_END = (size_t)page + p_size;
	while ((CURS_START = (size_t)cursor) < PAGE_END)
	{
		if (CURSOR->empty && (CURS_START + SIZE_HEAD + CURSOR->size) < PAGE_END
			&& NEXT_BLOC->empty)
			CURSOR->size = CURSOR->size + SIZE_HEAD + NEXT_BLOC->size;
		else
			cursor += CURSOR->size + SIZE_HEAD;
	}
	if (type == large || (type != large && page->empty
		&& (page->size == (p_size - SIZE_HEAD))))
		return (delete_page2(page, p_size, type));
	return (true);
}

bool		delete_page2(t_bloc *page, size_t p_size, enum e_type type)
{
	bool	null;
	size_t	i;

	null = false;
	i = ITERATOR(type) - 1;
	if (type != large && page == LIST[i])
	{
		if (page->next)
		{
			//teste de 2 page deu page tiny ou small et supp la premier
			*(G_LIST[i]) = page->next;
			(*(G_LIST[i]))->prev = NULL;
		}
		else
			null = true;
	}
	else if (type != large ||
			(type == large && page->prev != page && page->next != page))
	{
		if (page->prev)
			page->prev->next = page->next;
		if (page->next)
			page->next->prev = page->prev;
	}
	else if (type == large && page->prev == page && page->next == page)
		null = true;

	if (munmap(page, p_size) == -1)
		return (error(munmap_fail));
	if (null)
		*(G_LIST[i]) = NULL;
	return (true);
}

void		**check_ptr(void *ptr, enum e_fonction fonction)
{
	size_t			i;
	void			**start;
	t_bloc			*list;
	enum e_type		type;

	i = 0;
	start = NULL;
	g_mem.fonction = fonction;
	while (i < 3)
	{
		list = LIST[i];
		type = ((enum e_type[3]){tiny, small, large})[i];
		if ((start = check_list(ptr, list, type)))
		 	return (start);
		i++;
	}
	error(ptr_invalid);
	g_mem.fonction = ft_null;
	return (NULL);
}

void		**check_list(void *ptr, t_bloc *page, enum e_type type)
{
	size_t	p_limit[2];
	size_t	p_size;
	t_bloc	*bloc;

	PAGE_START = 0;
	PAGE_END = 0;
	while (page)
	{
		if (!check_corrupt(page, true, type))
			return (NULL);
		if ((PAGE_START == 0 || PAGE_END == 0) || type == large)
		{
			p_size = S_PAGE(type != large ? type : page->size);
			PAGE_START = (size_t)page;
			PAGE_END = (size_t)page + p_size;
		}
		if (PAGE_START <= (size_t)ptr && PAGE_END >= (size_t)ptr)
			return (!(bloc = check_page(ptr, page, p_size, type)) ?
				NULL : ((void*[2]){page, bloc}));
		page = page->next;
	}
	return (NULL);
}

void		*check_page(void *ptr, t_bloc *page, size_t p_size, enum e_type type)
{
	size_t	b_limit[2];
	void	*cursor;
	size_t	i;

	if (type == large)
		return (page);
	cursor = page;
	i = ITERATOR(type);
	//test avec dernier bloc == 1 place
	while ((size_t)cursor < ((size_t)page + p_size))
	{
		if (page != LIST[i - 1])
			check_corrupt(CURSOR, false, type);
		BLOC_START = (size_t)cursor;
		BLOC_END = (size_t)cursor + CURSOR->size + SIZE_HEAD;
		if (BLOC_START <= (size_t)ptr && BLOC_END >= (size_t)ptr)
		{
			if (!(type != large && CURSOR->empty) || g_mem.fonction != ft_realloc)
				return (cursor);
			error(empty_tiny + (i - 1));
		}
		cursor += CURSOR->size + SIZE_HEAD;
	}
	return (error(bloc_not_found));
}

bool		check_corrupt(t_bloc *ptr, bool page, enum e_type type)
{
	size_t			i;
	enum e_error	corrupt;

	i = ITERATOR(type);
	corrupt = corrupt_start;
	//TOUT TESTER
	//verifier avec le dernier bloc qui est de la taille de a page
	if ((type == tiny && (ptr->size > tiny)) ||
		(type == small && (ptr->size <= tiny || ptr->size > small)) ||
		(type == large && (ptr->size <= small || ptr->size > large)))
		return (error((page) ? corrupt + i : corrupt + i + 3));

	//((size_t)(LIST[i - 1]) + S_PAGE(type) + SIZE_HEAD) - ((size_t)(ptr) + SIZE_HEAD), (size_t)(ptr));
	//if (!page && (ptr->size > (((size_t)(LIST[i]) + type) - ((size_t)(ptr) + SIZE_HEAD))))
	//si la taille restante est plus grande que ce qu'il reste vraiment

	//verifier compartatif ptr
	if (page && type != large && (ptr != LIST[i - 1] && !LIST[i - 1]->next))
		return (error(corrupt + i + 6));
	if (type == large && (!ptr->prev || !ptr->next))
		return (error(corrupt + 9));
	if (type == large && ptr->empty)
		return (error(corrupt + 10));

	//faut t'il vraiment stop ?
	return (true);
}
