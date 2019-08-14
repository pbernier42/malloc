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
	size_t	octet;
	size_t	s_page;

	i = 0;
	octet = 0;
	while (i < 3)
		if ((page = ((t_bloc*[4]){G_TINY, G_SMALL, G_LARGE, NULL})[i++]))
		{
			if (page != G_LARGE)
				s_page = (page == G_TINY) ? T_SIZE_PAGE : S_SIZE_PAGE;
			else
				page = page->next;
			while ((page))
			{
				p_line((char*[2]){((char*[3]){"TINY : 0x", "SMALL : 0x",
					"LARGE : 0x"})[i - 1], "\n"}, (size_t[2]){
					((size_t[4]){9, 10, 10})[i - 1], 1}, (size_t)page, 16);
				octet = p_bloc(page,
					(i == 3) ? S_PAGE(page->size) : s_page, octet);
				page = (page == G_LARGE) ? NULL : page->next;
			}
		}
	p_line((char*[2]){"Total : ", " octets\n\n"}, (size_t[2]){8, 9}, octet, 10);
}

size_t	p_bloc(t_bloc *bloc, size_t s_page, size_t octet)
{
	void	*cursor;
	size_t	parsed;

	cursor = bloc;
	parsed = 0;
	while (parsed < s_page)
	{
		if (!CURSOR->empty)
		{
			p_line((char*[1]){"0x"}, (size_t[1]){2},
				(size_t)(cursor + SIZE_HEAD), 16);
			p_line((char*[1]){" - 0x"}, (size_t[1]){5},
				(size_t)(cursor + CURSOR->size + SIZE_HEAD), 16);
			p_line((char*[2]){" : ", " octets\n"},
				(size_t[2]){3, 8}, CURSOR->size, 10);
			octet += CURSOR->size;
		}
		parsed += CURSOR->size + SIZE_HEAD;
		cursor += CURSOR->size + SIZE_HEAD;
	}
	return (octet);
}

void	p_line(char **line, size_t *len, size_t number, size_t base)
{
	if (line && line[0])
		write(1, line[0], len[0]);
	if (base)
		p_posi(number, base);
	if (line && line[1])
		write(1, line[1], len[1]);
}

void	p_posi(size_t number, size_t base)
{
	size_t	rest;
	char	letter;

	rest = number % base;
	if (number >= base)
		p_posi(number /= base, base);
	else
		number /= base;
	letter = (rest > 9 ? (rest + 'A' - 10) : (rest + '0'));
	write(1, &letter, 1);
}
