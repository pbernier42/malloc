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

bool			delete_bloc(t_bloc *page, t_bloc *bloc);
bool			delete_page2(t_bloc *page, size_t p_size, enum e_type type);
void			**check_ptr(void *ptr);
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
#define PAGE_SIZE	size[0]
#define NEW_SIZE	size[1]

void		free2(void *ptr)
{
	void			**start;

	start = NULL;
	if (!ptr || !(start = check_ptr(ptr)))
		return ;
	if (!(delete_bloc(start[0], start[1])))
		return ;
}

bool		delete_bloc(t_bloc *page, t_bloc *bloc)
{
	void 		*cursor;
	enum e_type	type;
	size_t		size[2];
	size_t		p_limit[2];

	cursor = page;
	type = TYPE(bloc->size);
	bloc->empty = true;
	PAGE_SIZE = S_PAGE(bloc->size);
	PAGE_END = (size_t)page + PAGE_SIZE;
	while ((CURS_START = (size_t)cursor) < PAGE_END)
	{
		if (CURSOR->empty && (CURS_START + SIZE_HEAD + CURSOR->size) < PAGE_END
			&& NEXT_BLOC->empty)
		{
			NEW_SIZE = CURSOR->size + SIZE_HEAD + NEXT_BLOC->size;
			NEXT_BLOC->size = 0;
			CURSOR->size = NEW_SIZE;
			//a virer
		}
		else
			cursor += CURSOR->size + SIZE_HEAD;
	}
	if (type == LARGE || (type != LARGE && page->empty
		&& (page->size == (PAGE_SIZE - SIZE_HEAD))))
		return (delete_page2(page, PAGE_SIZE, type));
	return (true);
}

bool		delete_page2(t_bloc *page, size_t p_size, enum e_type type)
{
	bool	null;
	size_t	i;
	i = ITERATOR(type) - 1;


	null = false;

	if (type != LARGE && page == LIST[i])
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
	else if (type != LARGE ||
			(type == LARGE && page->prev != page && page->next != page))
	{
		if (page->prev)
			page->prev->next = page->next;
		if (page->next)
			page->next->prev = page->prev;
	}
	else if (type == LARGE && page->prev == page && page->next == page)
		null = true;

	if (munmap(page, p_size) == -1)
		return (error(munmap_fail));
	if (null)
		*(G_LIST[i]) = NULL;
	return (true);
}

void		**check_ptr(void *ptr)
{
	size_t			i;
	void			**start;
	t_bloc			*list;
	enum e_type		type;

	i = 0;
	start = NULL;
	if (!PROTECTED)
		return (check_list(ptr, LIST[ITERATOR(PTR->size) - 1],
			TYPE(PTR->size)));
	while (i < 3)
	{
		list = LIST[i];
		type = ((enum e_type[3]){TINY, SMALL, LARGE})[i];
		if ((start = check_list(ptr, list, type)))
		 	return (start);
		i++;
	}
	return (error(PTR_INVALID));
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
		if ((PAGE_START == 0 || PAGE_END == 0) || type == LARGE)
		{
			p_size = S_PAGE(type != LARGE ? type : page->size);
			PAGE_START = (size_t)page;
			PAGE_END = (size_t)page + p_size;
		}
		if (PAGE_START <= (size_t)ptr && PAGE_END >= (size_t)ptr)
		{
			//printf("p[%p]\np[%p]\na[%p]\na[%p]\n\n", G_TINY, page, &G_TINY, &page);
			if (!PROTECTED)
				return (((void*[2]){page, ptr}));
			return (!(bloc = check_page(ptr, page, p_size, type)) ?
				NULL : ((void*[2]){page, bloc}));
		}
		page = page->next;
	}
	return (NULL);
}

void		*check_page(void *ptr, t_bloc *page, size_t p_size, enum e_type type)
{
	size_t	b_limit[2];
	void	*cursor;
	size_t	i;

	if (type == LARGE)
		return (page);
	cursor = page;
	i = ITERATOR(type);
	//test avec dernier bloc == 1 place
	while ((size_t)cursor < ((size_t)page + p_size))
	{
		if (page != LIST[i - 1])
			check_corrupt(page, false, type);
		BLOC_START = (size_t)cursor;
		BLOC_END = (size_t)cursor + CURSOR->size + SIZE_HEAD;
		if (BLOC_START <= (size_t)ptr && BLOC_END >= (size_t)ptr)
			return(cursor);
	 	cursor += CURSOR->size + SIZE_HEAD;
	}
	return (error(BLOC_NOT_FOUND));
}

bool		check_corrupt(t_bloc *ptr, bool page, enum e_type type)
{
	size_t			i;
	enum e_error	corrupt;

	i = ITERATOR(type);
	corrupt = CORRUPT_START;
	//TOUT TESTER
	//verifier avec le dernier bloc qui est de la taille de a page
	if ((type == TINY && (ptr->size > TINY)) ||
		(type == SMALL && (ptr->size <= TINY || ptr->size > SMALL)) ||
		(type == LARGE && (ptr->size <= SMALL || ptr->size > LARGE)))
		return (error((page) ? corrupt + i : corrupt + i + 3));

	//((size_t)(LIST[i - 1]) + S_PAGE(type) + SIZE_HEAD) - ((size_t)(ptr) + SIZE_HEAD), (size_t)(ptr));
	//if (!page && (ptr->size > (((size_t)(LIST[i]) + type) - ((size_t)(ptr) + SIZE_HEAD))))
	//si la taille restante est plus grande que ce qu'il reste vraiment

	//verifier compartatif ptr
	if (page && type != LARGE && (ptr != LIST[i - 1] && !LIST[i - 1]->next))
		return (error(corrupt + i + 6));
	if (type == LARGE && (!ptr->prev || !ptr->next))
		return (error(corrupt + 9));
	if (type == LARGE && ptr->empty)
		return (error(corrupt + 10));

	//faut t'il vraiment stop ?
	return (true);
}
