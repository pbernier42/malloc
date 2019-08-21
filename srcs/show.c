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
	size_t octet;

	octet = p_page(G_TINY, "TINY : 0x", tiny);
	octet += p_page(G_SMALL, "SMALL : 0x", small);
	octet += p_page(G_LARGE->next, "LARGE : 0x", large);
	write(1, "Total : ", 8);
	p_posi(octet, 10);
	write(1, " octets\n\n", 9);
}

size_t	p_page(t_bloc *page, char *text, enum e_type type)
{
	size_t	octet;
	size_t	s_page;

	octet = 0;
	if (!page)
		return (octet);
	if (type != large)
		s_page = S_PAGE(type);
	while (page)
	{
		write(1, text, (type == tiny) ? 9 : 10);
		p_posi((size_t)page, 16);
		write(1, "\n", 1);
		if (type == large)
			s_page = S_PAGE(page->size);
		octet += p_bloc(page, s_page, type);
		page = (page == G_LARGE) ? NULL : page->next;
	}
	return (octet);
}

size_t	p_bloc(t_bloc *bloc, size_t s_page, enum e_type type)
{
	size_t	octet;
	void	*cursor;
	size_t	page_end;
	size_t	align;

	octet = 0;
	cursor = bloc;
	page_end = (size_t)cursor + s_page;
	while ((size_t)cursor < page_end)
	{
		align = (type != large) ? A_SIZE(CURSOR->size) : (s_page - SIZE_HEAD);
		if (!CURSOR->empty || CURSOR->empty)
		{
			write(1, "0x", 2);
			p_posi((size_t)(cursor + SIZE_HEAD), 16);
			write(1, " - 0x", 5);
			p_posi((size_t)(cursor + align + SIZE_HEAD), 16);
			write(1, " : ", 3);
			p_posi(CURSOR->size, 10);
			write(1, " octets", 8);
			if (!CURSOR->empty)
				octet += CURSOR->size;
			else
				printf(" (EMPTY)");
			printf("\n");

		}
		cursor += (align + SIZE_HEAD);
	}
	return (octet);
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
