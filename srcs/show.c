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

void	show_alloc_mem()
{
	t_bloc	*start;
	size_t	octets;

	octets = 0;
	if (g_mem.tiny)
	{
		start = g_mem.tiny;
		write(1, "TINY : 0x", 9);
		print_posi((size_t)g_mem.tiny, 16);
		write(1, "\n", 1);
		while ((g_mem.tiny))
		{
			octets += print_page(g_mem.tiny, T_SIZE_PAGE);
			g_mem.tiny = g_mem.tiny->next;
		}
		g_mem.tiny = start;
	}
	if (g_mem.small)
	{
		start = g_mem.small;
		write(1, "SMALL : 0x", 9);
		print_posi((size_t)g_mem.small, 16);
		write(1, "\n", 1);
		while ((g_mem.small))
		{
			octets += print_page(g_mem.small, S_SIZE_PAGE);
			g_mem.small = g_mem.small->next;
		}
		g_mem.small = start;
	}
	if (g_mem.large)
	{
		printf("?\n");
		start = g_mem.large;
		write(1, "LARGE : 0x", 9);
		print_posi((size_t)g_mem.large, 16);
		write(1, "\n", 1);
		g_mem.large = g_mem.large->next;
		//gerer cas ou il y a une seul page
		while (g_mem.large != start)
		{
			octets += print_page(g_mem.large, g_mem.large->size + SIZE_HEAD);
			g_mem.large = g_mem.large->next;
		}
		g_mem.large = start;
	}
	write(1, "Total : ", 9);
	print_posi(octets, 10);
	write(1, " octets\n", 8);
}

size_t	print_page(t_bloc *bloc, size_t s_page)
{
	void	*cursor;
	size_t	parsed;
	size_t	octets;

	cursor = bloc;
	parsed = 0;
	octets = 0;
	while (parsed < s_page)
	{
		//printf("{%lu < %lu}\n", parsed, s_page);
		//printf("%p - ", cursor + SIZE_HEAD);
		//printf("%p...\n", cursor + CURSOR->size + SIZE_HEAD);
		if (!CURSOR->empty)
		{
			write(1, "0x", 2);
			print_posi((size_t)(cursor + SIZE_HEAD), 16);
			write(1, " - 0x", 5);
			print_posi((size_t)(cursor + CURSOR->size + SIZE_HEAD), 16);
			write(1, " : ", 3);
			octets += CURSOR->size;
			print_posi(CURSOR->size, 10);
			write(1, " octets\n", 8);
		}
		parsed += CURSOR->size + SIZE_HEAD;
		cursor += CURSOR->size + SIZE_HEAD;
	}
	return (octets);
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
