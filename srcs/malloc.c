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

	start = *page;
	while (type != large && (*page) && (*page)->next)
		(*page) = (*page)->next;
	if (((new = mmap(0, s_page, FL_PROT, FL_MAP, -1, 0)) == MAP_FAILED))
		return (false);
	if (type == large && !(*page))
		*new = ((t_bloc){size - SIZE_HEAD, true, new, new});
	else if (type == large && (*page))
	{
		*new = ((t_bloc){size - SIZE_HEAD, true, (*page), (*page)->next});
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
	t_bloc	**better;

	better = NULL;
	if (!page || (type == large && !page->empty)
		|| (type != large && !(better = find_best(size, page,
			S_PAGE(size), S_BLOC_MIN(size)))))
		return (NULL);
	place_header(size, (type == large && page->empty) ?
		((t_bloc*[2]){page, page}) : ((t_bloc*[2]){BETTER_PAGE, BETTER_BLOC}),
		type, ft_malloc);
	return (BETTER_BLOC + SIZE_HEAD);
}

t_bloc		**find_best(size_t size, t_bloc *page, size_t s_page, size_t s_min)
{
	size_t	align[3];
	t_bloc	*better[2];
	void	*cursor;
	size_t	parsed;

	BETTER_BLOC = NULL;
	AS_NEW = A_SIZE(size);

	//printf("1\n");
	while (page && (!BETTER_BLOC || (BETTER_BLOC && AS_BET == AS_NEW)))
	{

		cursor = page;
		parsed = 0;
		while (parsed < s_page)
		{

			AS_CUR = A_SIZE(CURSOR->size);
			if ((CURSOR->empty)
				&& (AS_CUR == AS_NEW
					|| AS_CUR > AS_NEW + SIZE_HEAD + A_SIZE(s_min))
				&& (!BETTER_BLOC ||
					(BETTER_BLOC && !(AS_BET == AS_NEW) && (AZ_BET > AZ_CUR))))
					{
						BETTER_PAGE = page;
						BETTER_BLOC = CURSOR;
						AS_BET = A_SIZE(BETTER_BLOC->size);
					}
			parsed += AS_CUR + SIZE_HEAD;
			cursor += AS_CUR + SIZE_HEAD;
		}
		page = page->next;
	}
	// printf("%zu--\n\n", better->size);
	// if (size == 9)
	// {
	//  	show_dump_mem(((t_bloc*)(better)));
	//  	//show_dump_mem(((t_bloc*)(BETTER + (SIZE_HEAD + AS_NEW))));
	// }
//	printf("%p\n", better);
	return ((t_bloc*[2]){BETTER_PAGE, BETTER_BLOC});
}

void		place_header(size_t size, t_bloc *better[2], enum e_type type,
				enum e_fonction fonction)
{
	size_t	align[3];


	BETTER_BLOC->empty = false;
	if (type == large || BETTER_BLOC->size == size)
		return ;


	AS_NEW = A_SIZE(size);
	//printf("?\n");
	AS_BET = A_SIZE(BETTER_BLOC->size);
	if (BETTER_PAGE != G_TINY)
		printf("YEEEE\n");
	//printf("[%p]\n[%zu]\n[%zu]\n\n",
	//	G_TINY, (size_t)(BETTER + SIZE_HEAD + AS_BET), ((size_t)page) + S_PAGE(type));
	// if (size == 9)
	// {
	//  	show_dump_mem(((t_bloc*)(BETTER)));
	//  	//show_dump_mem(((t_bloc*)(BETTER + (SIZE_HEAD + AS_NEW))));
	// }
	// if (size)
	// {
	// 	printf("size = %zu\n", size);
	//  	printf("size = %zu\n", better->size);
	//  	printf("empty = %d\n", ((t_bloc*)(BETTER + (SIZE_HEAD + AS_NEW)))->empty);
	//  	printf("???? = %zu %zu %zu\n\n", AS_BET, SIZE_HEAD, AS_NEW);
	// }


	if (((size_t)BETTER_BLOC + AS_NEW) - ((size_t)BETTER_PAGE + S_PAGE(BETTER_PAGE->size) < SIZE_HEAD + A_SIZE(MIIIIIIIN))

		printf("%zu\n%zu\n", (size_t)BETTER_BLOC + AS_NEW + SIZE_HEAD, (size_t)BETTER_PAGE + SIZE_HEAD + S_PAGE(BETTER_PAGE->size));

	if (((t_bloc*)(BETTER + (SIZE_HEAD + AS_NEW)))->size > type ||
		!((t_bloc*)(BETTER + (SIZE_HEAD + AS_NEW)))->size)
	{

		((t_bloc*)(BETTER + (SIZE_HEAD + AS_NEW)))->size = (fonction == ft_realloc) ?
			((t_bloc*)(BETTER + (SIZE_HEAD + AS_BET)))->size - (AS_BET - AS_NEW) :
			(AS_BET - SIZE_HEAD - AS_NEW);
		((t_bloc*)(BETTER + (SIZE_HEAD + AS_NEW)))->empty = true;
	}
	//printf("2\n");
	BETTER_BLOC->size = size;

}
