/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbernier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 15:35:56 by pbernier          #+#    #+#             */
/*   Updated: 2019/06/07 15:35:57 by pbernier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

t_type		g_mem;

void		show_dump_mem(void *ptr)
{
	t_posi	posi;

	posi = check_ptr(ptr, ft_dump);
	if (!(P_BLOC))
		return ;
	p_dump(BLOC, P_BLOC, 0, false);
	p_dump(BLOC + SIZE_HEAD, NULL, P_BLOC->size, true);
	G_FONCTION = ft_null;
}

void		p_dump(void *ptr, t_bloc *header, size_t size, bool data)
{
	size_t	i[2];
	char	raw[PART * 2];

	I = 0;
	while (((!data) && I < 4) || (data && (LINE * (PART * 2) < size)))
	{
		COL = 0;
		write(1, "0x", 2);
		p_posi((size_t)ptr, 16);
		while ((!data && COL < (size_t[4]){8, 8, 8, 8}[I])
			|| (data && (COL < (PART * 2)
				&& (((LINE) * (PART * 2)) + COL) < size)))
		{
			p_oct(ptr, COL++);
			if ((data))
				raw[COL - 1] = (OCT >= ' ' && OCT <= '~') ? OCT : '.';
			++ptr;
		}
		!data ? p_raw(NULL, COL, header, ptr) : p_raw(raw, COL, NULL, ptr);
		++I;
	}
	write(1, "\n", 1);
}

void		p_oct(void *ptr, size_t i)
{
	static bool	colored;

	if (i == 0)
		write(1, " ", 1);
	write(1, i == PART ? "\t" : " ", 1);
	if (!OCT && (!colored || i == 0))
	{
		write(1, GREY, 9);
		colored = true;
	}
	if (OCT && colored)
	{
		write(1, RESET, 4);
		colored = false;
	}
	write(1, (char[2]){
		(OCT / 16) > 9 ? (OCT / 16) + 'A' - 10 : (OCT / 16) + '0',
		(OCT % 16) > 9 ? (OCT % 16) + 'A' - 10 : (OCT % 16) + '0'}, 2);
}

void		p_raw(char raw[PART * 2], size_t size, t_bloc *header, void *ptr)
{
	size_t			i;
	static size_t	printed;

	if (!*((unsigned char*)(ptr - 1)))
		write(1, RESET, 4);
	i = 0;
	while (size + i < (PART * 2))
		write(1, size + i++ == PART ? "\t  " : "   ", 3);
	write(1, "  |", 3);
	if (!header)
		write(1, raw, size);
	else
	{
		p_head((printed != 3 ? printed : 2),
			((size_t[4]){header->size, header->empty,
				(size_t)header->prev, (size_t)header->next})[printed],
			((size_t[4]){10, 0, 16, 16})[printed]);
		printed += (printed != 3) ? 1 : -3;
	}
	write(1, "|\n", 2);
}

void		p_head(size_t printed, size_t number, size_t base)
{
	if (printed != 0 && (!number || printed == 1))
		(printed == 1 && !number) ? write(1, "false", 5) :
			write(1, ((char*[3]){"true", "NULL"})[printed - 1], 4);
	else
		p_posi(number, base);
}
