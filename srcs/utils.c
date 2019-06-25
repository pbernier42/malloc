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
	enum e_type	type;

	type = 0;
	while (size > ((size_t[4]){0, TINY, SMALL, size})[type] && size <= LARGE)
		++type;
	return (((size_t[5]){
		((size_t[4]){0, T_SIZE_PAGE, S_SIZE_PAGE, size + SIZE_HEAD})[type],
		((size_t[4]){0, TINY, SMALL, LARGE})[type],
		((size_t[4]){0, T_SIZE_ZERO, S_SIZE_ZERO, 0})[type],
		((size_t[4]){0, 1, T_SIZE_BLOC + 1, S_SIZE_BLOC + 1})[type],
		type})[i]);
}

void		*error(int error)
{
	if (error == MUNMAP_FAIL)
		error = 1;
	else if (!(error >= ERROR_START && error <= ERROR_END))
		error = UNKNOWN_ERROR;

	printf("{%d} \n", error);
	//tous reverif
	write(2, ((char*[16]){
		"UNKNOWN ERROR\n",
		"PAS REUSSI A MUNMAP\n",
		"PTR PAS A NOUS\n",
		"PTR A NOUS MAIS PROBABLEMENT CORROMPU\n",
		"TINY PAGES'S SIZE INVALID\n",
		"SMALL PAGES'S SIZE INVALID\n",
		"LARGE PAGES'S SIZE INVALID\n",
		"TINY BLOC'S SIZE INVALID\n",
		"SMALL BLOC'S SIZE INVALID\n",
		"LARGE BLOC'S SIZE INVALID\n",
		"TINY LIST LINK INVALID\n",
		"SMALL LIST LINK INVALID\n",
		"LARGE LIST LINK INVALID\n",
		"LARGE EMPTY INVALID\n",
		"BLOC NOT FOUND IN HIS PAGE\n"
		})[error],
		((size_t[16]){
			14, 20, 15, 38, 26, 27, 27,
			25, 26, 26, 23,	24, 24,
			20, 27})[error]);
	return (NULL);
}

bool		delete_page(t_bloc *prev, t_bloc *cursor, t_bloc *next)
{
	if (prev)
		((t_bloc*)prev)->next = next;
	if (next)
		((t_bloc*)next)->prev = prev;
	if ((munmap(cursor, CURSOR->size + SIZE_HEAD)))
		return (false);
	return (true);
}

bool		do_i_have_to_delete_page(void *cursor, size_t page_size)
{
	if (cursor && CURSOR->empty && CURSOR->size + SIZE_HEAD >= page_size)
		return (true);
	return (false);
}
