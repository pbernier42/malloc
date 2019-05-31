/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbernier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 14:43:38 by pbernier          #+#    #+#             */
/*   Updated: 2019/05/06 14:43:39 by pbernier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

t_type		g_mem;

void	show_alloc_mem(void)
{
	t_bloc	*page;
	size_t	i;
	size_t	octets;
	size_t	s_page;

	i = 0;
	octets = 0;
	while (i < 3)
		if ((page = ((t_bloc*[4]){G_TINY, G_SMALL, G_LARGE, NULL})[i++]))
		{
			s_page = S_PAGE(page->size);
			print_line((char*[2]){
			((char*[3]){"TINY : 0x", "SMALL : 0x", "LARGE : 0x"})[i - 1], "\n"},
			(size_t[2]){((size_t[4]){9, 10, 10})[i - 1], 1}, (size_t)page, 16);
			if (page == G_LARGE)
				page = page->next;
			while ((page))
			{
				octets = print_bloc(page, s_page, octets);
				page = (page == G_LARGE) ? NULL : page->next;
			}
		}
	print_line((char*[2]){"Total : ", " octets\n"},
	(size_t[2]){8, 8}, octets, 10);
}

size_t	print_bloc(t_bloc *bloc, size_t s_page, size_t octets)
{
	void	*cursor;
	size_t	parsed;

	cursor = bloc;
	parsed = 0;
	while (parsed < s_page)
	{
		if (!CURSOR->empty)
		{
			print_line((char*[1]){"0x"}, (size_t[1]){2},
			(size_t)(cursor + SIZE_HEAD), 16);
			print_line((char*[2]){" - 0x"}, (size_t[1]){5},
			(size_t)(cursor + CURSOR->size + SIZE_HEAD), 16);
			print_line((char*[2]){" : ", " octets\n"},
			(size_t[2]){3, 8}, CURSOR->size, 10);
			octets += CURSOR->size;
		}
		parsed += CURSOR->size + SIZE_HEAD;
		cursor += CURSOR->size + SIZE_HEAD;
	}
	return (octets);
}

void	print_line(char **line, size_t *len, size_t number, size_t base)
{
	(line) && line[0] ? write(1, line[0], len[0]) : 0;
	(base) ? print_posi(number, base) : 0;
	(line) && line[1] ? write(1, line[1], len[1]) : 0;
}

void	print_posi(size_t number, size_t base)
{
	size_t	rest;
	char	letter;

	rest = number % base;
	if (number >= base)
		print_posi(number /= base, base);
	else
		number /= base;
	letter = (rest > 9 ? (rest + 'A' - 10) : (rest + '0'));
	write(1, &letter, 1);
}
