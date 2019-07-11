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
		(((size_t[4]){0, tiny, tiny, tiny})[type]),
		(((size_t[4]){0, T_SIZE_ZERO, S_SIZE_ZERO, 0})[type]),
		(((size_t[4]){0, 1, T_SIZE_BLOC + 1, S_SIZE_BLOC + 1})[type]),
		type})[i]);
}

void		*error(int error)
{
	if (!PRINT_ERROR)
		return (NULL);
	if (error == MUNMAP_FAIL)
		error = 1;
	else if (!(error >= error_start && error < error_end))
		error = unknown_error;

	write(1, GREY, 9);
	write(2, ((char*[5]){"[???] - ", "[Malloc] - ", "[Realloc] - ",
		"[Free] - ", "[Dump] - "})[g_mem.fonction],
		((size_t[5]){8, 11, 12, 9, 9})[g_mem.fonction]);
	write(1, RESET, 4);
	write(2, ((char*[18]){"UNKNOWN ERROR\n", "PAS REUSSI A MUNMAP\n",
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
