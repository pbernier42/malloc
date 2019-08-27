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

t_type		g_mem;

size_t		finder(size_t size, size_t i)
{
	size_t	type;

	type = 0;
	while (size > ((size_t[4]){tiny, small, size})[type])
		++type;
	return (((size_t[5]){
		(((size_t[3]){T_SIZE_PAGE, S_SIZE_PAGE, L_SIZE_PAGE(size)})[type]),
		(((size_t[3]){tiny, small, large})[type]),
		(((size_t[3]){T_SIZE_ZERO, S_SIZE_ZERO, 0})[type]),
		(((size_t[3]){1, T_SIZE_BLOC + 1, S_SIZE_BLOC + 1})[type]),
		type})[i]);
}

void		*ft_error(int error)
{
	if (!PRINT_ERROR)
		return (NULL);
	else if (!(error > error_start && error < error_end))
		error = unknown_error;
	write(2, GREY, 9);
	write(2, ((char*[5]){"[???] - ", "[Malloc] - ", "[Realloc] - ", "[Free] - ",
		"[Dump] - "})[G_FONCTION], ((size_t[5]){8, 11, 12, 9, 9})[G_FONCTION]);
	write(2, RESET, 4);
	write(2, ((char*[23]){
		"UNKNOWN ERROR\n", "PAS REUSSI A MUNMAP\n",
		"NO VALIDE PTR FOUND IN OUR PAGES\n",
		"PTR A NOUS MAIS PROBABLEMENT CORROMPU\n",
		"TINY PAGES'S SIZE INVALID\n", "SMALL PAGES'S SIZE INVALID\n",
		"LARGE PAGES'S SIZE INVALID\n", "TINY BLOC'S SIZE INVALID\n",
		"SMALL BLOC'S SIZE INVALID\n", "LARGE BLOC'S SIZE INVALID\n",
		"TINY LIST LINK INVALID\n", "SMALL LIST LINK INVALID\n",
		"LARGE LIST LINK INVALID\n", "LARGE EMPTY INVALID\n",
		"TINY EMPTY INVALID\n", "SMALL EMPTY INVALID\n",
		"BLOC NOT FOUND IN HIS PAGE\n", "TINY BLOC NOT ALIGN\n",
		"SMALL BLOC NOT ALIGN\n", "LARGE BLOC NOT ALIGN\n",
		"TINY PAGE NOT ALIGN\n", "SMALL PAGE NOT ALIGN\n",
		"LARGE PAGE NOT ALIGN\n"})[error],
		((size_t[23]){14, 20, 33, 38, 26, 27, 27, 25, 26, 26, 23, 24, 24, 20,
			19, 20, 27, 20, 21, 21, 20, 21, 22})[error]);
	return (NULL);
}
