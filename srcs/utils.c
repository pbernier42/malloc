/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlecart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 19:57:04 by rlecart           #+#    #+#             */
/*   Updated: 2019/05/31 18:52:30 by rlecart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

size_t		finder(size_t size, size_t i)
{
	size_t	type;

	type = 0;
	while (size > ((size_t[4]){0, tiny, small, size})[type] && size <= large)
		++type;
	return (((size_t[5]){
		(((size_t[4]){0, T_SIZE_PAGE, S_SIZE_PAGE, size + SIZE_HEAD})[type]),
		(((size_t[4]){0, tiny, small, large})[type]),
		(((size_t[4]){0, T_SIZE_ZERO, S_SIZE_ZERO, 0})[type]),
		(((size_t[4]){0, 1, T_SIZE_BLOC + 1, S_SIZE_BLOC + 1})[type]),
		type})[i]);
}

void		*error(int error)
{
	if (!PRINT_ERROR)
		return (NULL);
	else if (!(error > error_start && error < error_end))
		error = unknown_error;
	write(1, GREY, 9);
	write(2, ((char*[5]){
		"[???] - ", "[Malloc] - ", "[Realloc] - ", "[Free] - ",
			"[Dump] - "})[g_mem.fonction],
		((size_t[5]){8, 11, 12, 9, 9})[g_mem.fonction]);
	write(1, RESET, 4);
	write(2, ((char*[18]){
		"UNKNOWN ERROR\n", "PAS REUSSI A MUNMAP\n",
		"NO VALIDE PTR FOUND IN OUR PAGES\n",
		"PTR A NOUS MAIS PROBABLEMENT CORROMPU\n",
		"TINY PAGES'S SIZE INVALID\n", "SMALL PAGES'S SIZE INVALID\n",
		"LARGE PAGES'S SIZE INVALID\n", "TINY BLOC'S SIZE INVALID\n",
		"SMALL BLOC'S SIZE INVALID\n", "LARGE BLOC'S SIZE INVALID\n",
		"TINY LIST LINK INVALID\n", "SMALL LIST LINK INVALID\n",
		"LARGE LIST LINK INVALID\n", "LARGE EMPTY INVALID\n",
		"TINY EMPTY INVALID\n", "SMALL EMPTY INVALID\n",
		"BLOC NOT FOUND IN HIS PAGE\n"})[error],
		((size_t[18]){14, 20, 33, 38, 26, 27, 27, 25, 26, 26, 23, 24, 24, 20,
			19, 20, 27})[error]);
	return (NULL);
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
			p_size = S_PAGE(type != large ? type : page->size);
		PAGE_START = (size_t)page;
		PAGE_END = (size_t)page + p_size;
		if (PAGE_START <= (size_t)ptr && PAGE_END >= (size_t)ptr)
			return (!(bloc = check_page(
				ptr, page, p_size, type)) ? NULL : ((void*[2]){page, bloc}));
		if (type == large && page->next == g_mem.large)
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

	if (type == large)
		return (page);
	cursor = page;
	i = ITERATOR(type);
	while ((size_t)cursor < ((size_t)page + p_size))
	{
		if (page != LIST[i - 1])
			check_corrupt(CURSOR, false, type);
		BLOC_START = (size_t)cursor;
		BLOC_END = (size_t)cursor + CURSOR->size + SIZE_HEAD;
		if (BLOC_START <= (size_t)ptr && BLOC_END >= (size_t)ptr)
		{
			if (!(type != large && CURSOR->empty)
				|| g_mem.fonction != ft_realloc)
				return (cursor);
			return (error(empty_tiny + (i - 1)));
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
	if (!ptr->size
		|| (!ptr->empty
			&& ((type == tiny && (ptr->size > tiny))
			|| (type == small && (ptr->size <= tiny || ptr->size > small))
			|| (type == large && (ptr->size <= small || ptr->size > large))))
		|| (ptr->empty && (ptr->size > S_PAGE(type))))
		return (error((page) ? corrupt + i : corrupt + i + 3));
	if (page && type != large && (ptr != LIST[i - 1] && !LIST[i - 1]->next))
		return (error(corrupt + i + 6));
	if (type == large && (!ptr->prev || !ptr->next))
		return (error(corrupt + 9));
	if (type == large && ptr->empty)
		return (error(corrupt + 10));
	return (true);
}
