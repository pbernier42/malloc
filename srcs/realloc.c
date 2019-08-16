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

t_type		g_mem;

void		*realloc(void *ptr, size_t size)
{
	void		**start;
	void		*page;
	size_t		s_prev;
	enum e_type	type;

	//printf("1 = %zu\n", size);
	if (!ptr || !size)
		return (malloc(size));
	//printf("2 = %zu\n", size);
	if (!(start = check_ptr(ptr, ft_realloc)))
		return (NULL);
	//printf("3 = %zu\n", size);
	page = start[0];
	ptr = start[1];
	type = TYPE(size);
	if (PTR->size == size && !(G_FONCTION = ft_null))
		return (ptr + SIZE_HEAD);
	//printf("4 = %zu\n", size);
	if (!move_bloc(ptr, size, type))
	{
		//printf("5 = %zu\n", size);
		return (reset(page, ptr + SIZE_HEAD, PTR->size, size));
	}

	if (type == large && PTR->size > size)
		if (munmap(ptr + SIZE_HEAD + size, PTR->size - size) == MUNMAP_FAIL)
			return (ft_error(munmap_fail));

	if (HISTORY)
		s_prev = PTR->size;
	place_header(size, ((t_bloc*[2]){page, ptr}), type, ft_realloc);
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
		|| (type != large && PTR->size > size
			&& PTR->size < (SIZE_HEAD + s_min + size)))
		return (false);
	s_page = S_PAGE(PTR->size);
	cursor = (type == tiny) ? G_TINY : G_SMALL;
	while (!(ptr >= cursor && ptr < (cursor + s_page)))
		cursor = CURSOR->next;
	if (((ptr + SIZE_HEAD + PTR->size) == cursor + s_page)
		|| !(((t_bloc*)(ptr + SIZE_HEAD + PTR->size))->empty)
		|| !(PTR->size + ((t_bloc*)(ptr + SIZE_HEAD + PTR->size))->size >
			size + s_min))
		return (false);
	return (true);
}

void		*reset(t_bloc *page, void *ptr, size_t s_prev, size_t size)
{
	void	*prev;
	void	*ret;


	if (HISTORY)
		prev = ptr;
	ret = malloc(size);
	//printf("6 = %zu | %zu\n", size, s_prev);
	copy_data(ret, ptr, ((size_t[2]){size, s_prev}));
	delete_bloc(page, ptr);
	add_histo((t_hist){true, ft_realloc, {prev, ret != prev ? ret : NULL},
		{s_prev, ret ? ((t_bloc*)(ret - SIZE_HEAD))->size : 0}});
	return (ret);
}

void		copy_data(void *new, void *data, size_t len[2])
{
	size_t	i;
	size_t	limit;

	i = 0;
	//printf("7 = %zu | %zu\n", S_NEW, S_DATA);
	limit = S_NEW < S_DATA ? S_NEW : S_DATA;
	//printf("7 = %zu \n", limit);
	//printf("8 = %p | %p\n", NEW, DATA);
	while (i++ < limit)
		NEW[i - 1] = DATA[i - 1];
}
