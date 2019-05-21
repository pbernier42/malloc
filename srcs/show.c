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
	if (g_mem.tiny)
	{
		write(1, "TINY : 0x", 9);
		print_posi((size_t)g_mem.tiny, 16);
		write(1, "\n", 1);
		printf("[%p]\n", g_mem.tiny);
		print_adre(&g_mem.tiny);
	}
	if (g_mem.small)
		write(1, "SMALL : ", 7);

	if (g_mem.large)
		write(1, "LARGE : ", 7);
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
	letter = (rest > 9 ? (rest + 'a' - 10) : (rest + '0'));
	write(1, &letter, 1);
}

// void	print_page(t_bloc **bloc)
// {
//
// }

void	print_adre(t_bloc **bloc)
{
	print_posi((size_t)(*bloc) + sizeof(t_bloc), 16);
	write(1, " - ", 3);
	print_posi((size_t)(*bloc) + sizeof(t_bloc) + (*bloc)->size, 16);
	write(1, " : ", 3);
	print_posi((*bloc)->size, 10);
	write(1, " octets\n", 8);
}
