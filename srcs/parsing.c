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

void		**check_ptr(void *ptr, enum e_fonction fonction)
{
	size_t			i;
	void			**start;
	t_bloc			**list;
	enum e_type		type;

	i = 0;
	start = NULL;
	G_FONCTION = fonction;

	while (i < 3)
	{
		list = G_LIST[i];
		type = ((enum e_type[3]){tiny, small, large})[i];

		if ((start = check_list(ptr, *list, type)))
			return (start);
		i++;
	}
	ft_error(ptr_invalid);
	G_FONCTION = ft_null;
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
			p_size = S_PAGE(type != large ? type : page->size);
		PAGE_START = (size_t)page;
		PAGE_END = (size_t)page + p_size;
		if (PAGE_START <= (size_t)ptr && PAGE_END >= (size_t)ptr)
		{
			return (!(bloc = check_page(ptr, page, p_size, type)) ?
				NULL : ((void*[2]){page, bloc}));
		}
		if (type == large && page->next == G_LARGE)
			return (NULL);
		else
			page = page->next;
	}
	return (NULL);
}

void		*check_page(void *ptr, t_bloc *page, size_t p_size,
		enum e_type type)
{
	size_t	b_limit[2];
	void	*cursor;
	size_t	i;
	size_t	align[1];
	int q =1;

	if (type == large)
		return (page);
	cursor = page;
	i = ITERATOR(type);
	while ((size_t)cursor < ((size_t)page + p_size))
	{
		printf("{{{{{%i}}}}}\n", q);
		//printf("A=[%p]\nS=[%zu]\n[%p][%p]\n", CURSOR, CURSOR->size, CURSOR->prev, CURSOR->next);
		//printf("[%zu]< [%zu] (%zu)\n", (size_t)cursor, ((size_t)page + p_size), p_size);
		if (page != LIST[i - 1])
			check_corrupt(CURSOR, false, type);
		AS_CUR = A_SIZE(CURSOR->size);
		printf("%zu  %zu\n\n", CURSOR->size, AS_CUR);

		BLOC_START = (size_t)cursor;
		BLOC_END = (size_t)cursor + AS_CUR + SIZE_HEAD;
		// printf("S = [%zu]\nC = [%zu]\nE = [%zu]\n\n",
		// 	BLOC_START % 1000, (size_t)cursor % 1000, BLOC_END % 1000);
		if  (q++ == 5)
		{
			while(1)
				;
		}

		/////?????
		printf("P[%zu]\ne[%zu]\n\n", (size_t)cursor, BLOC_END);
		if (BLOC_START <= (size_t)ptr)
			printf("1\n");
		if (BLOC_END >= (size_t)ptr)
			printf("2\n");

		printf("%p\n", ptr);
		if (BLOC_START <= (size_t)ptr && BLOC_END >= (size_t)ptr)
		{
			printf("?\n");
			if (!(type != large && CURSOR->empty) || G_FONCTION != ft_realloc)
				return (cursor);
			return (ft_error(empty_tiny + (i - 1)));
		}
	//	printf("---%zu (%zu)\n", CURSOR->size, AS_CUR);
		print
		cursor += AS_CUR + SIZE_HEAD;
	//	printf("[%zu]< [%zu] (%zu)\n\n",
		//	(size_t)cursor % 1000, ((size_t)page + p_size) % 1000, p_size);
	}
	return (ft_error(bloc_not_found));
}

bool		check_corrupt(t_bloc *ptr, bool page, enum e_type type)
{
	size_t			i;
	enum e_error	corrupt;

	i = ITERATOR(type);
	if (((size_t)ptr % A_NB) != 0)
		return(ft_error(((page) ? page_align_tiny : bloc_align_tiny) + i - 1));
	corrupt = corrupt_start;
	if (!ptr->size
		|| (!ptr->empty
			&& ((type == tiny && (ptr->size > tiny))
			|| (type == small && (ptr->size <= tiny || ptr->size > small))
			|| (type == large && (ptr->size <= small || ptr->size > large))))
		|| (ptr->empty && (ptr->size > S_PAGE(type))))
		return (ft_error((page) ? corrupt + i : corrupt + i + 3));
	if (page && type != large && (ptr != LIST[i - 1] && !LIST[i - 1]->next))
		return (ft_error(corrupt + i + 6));
	if (type == large && (!ptr->prev || !ptr->next))
		return (ft_error(corrupt + 9));
	return (true);
}
