/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbernier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 14:43:32 by pbernier          #+#    #+#             */
/*   Updated: 2019/05/31 18:15:34 by rlecart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

void		*realloc(void *ptr, size_t size)
{
	void	**start;
	void	*page;
	size_t	s_prev;
	enum e_type	type;

	if (!ptr || !size)
		return (malloc(size));

	if (size == small - 2)
		g_mem.i = true;

	if (!(start = check_ptr(ptr, ft_realloc)))
		return (ptr);
	page = start[0];
	ptr = start[1];
	type = TYPE(size);
	if (PTR->size == size && !(g_mem.fonction = ft_null))
		return (ptr + SIZE_HEAD);
	if (!move_bloc(ptr, size, type))
		return (reset(page, ptr + SIZE_HEAD, PTR->size, size));
	if (type == large && PTR->size > size)
		if (munmap(ptr + SIZE_HEAD + size, PTR->size - size) == MUNMAP_FAIL)
			return (error(MUNMAP_FAIL));
	if (HISTORY)
		s_prev = PTR->size;
	place_header(size, ptr, type, ft_realloc);
	add_histo((t_hist){true, ft_realloc, {ptr + SIZE_HEAD, NULL},
		{s_prev, size}});
	return (ptr + SIZE_HEAD);
}

bool		move_bloc(void *ptr, size_t size, enum e_type type)
{
	size_t	s_min;
	size_t	s_page;
	void	*cursor;

	s_min = S_BLOC_MIN(PTR->size);
	if (!ptr || type != TYPE(PTR->size) || (type == large && PTR->size < size)
		|| (type != large && PTR->size > size && PTR->size <
		(SIZE_HEAD + s_min + size)))
		return (false);
	s_page = S_PAGE(PTR->size);
	cursor = (type == tiny) ? G_TINY : G_SMALL;
	while (!(ptr >= cursor && ptr < (cursor + s_page)))
		cursor = CURSOR->next;
	if (((ptr + SIZE_HEAD + PTR->size) == cursor + s_page) ||
		!(((t_bloc*)(ptr + SIZE_HEAD + PTR->size))->empty) ||
		!(PTR->size + ((t_bloc*)(ptr + SIZE_HEAD + PTR->size))->size >
		size + s_min))
		return (false);
	return (true);
}

void		*reset(t_bloc *page, void *ptr, size_t s_prev, size_t size)
{
	void 	*prev;
	void	*ret;

	printf("\033[31m[WARNING]\033[0m free\n");
	if (HISTORY)
		prev = ptr;
	delete_bloc(page, ptr);
	ret = malloc(size);
	add_histo((t_hist){true, ft_realloc, {prev, ret != prev ? ret : NULL},
			{s_prev, ret ? ((t_bloc*)(ret - SIZE_HEAD))->size : 0}});
	return (ret);
}
