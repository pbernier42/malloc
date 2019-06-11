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

# define PART	8
# define LINE	i[0]
# define COL	i[1]
# define OCT	*((unsigned char*)ptr)

# define RESET				"\033[0m"
// # define RED				"\033[38;5;1m"
// # define RED_MINUS			"\033[38;5;9m"
// # define GREEN_MINUS		"\033[38;5;10m"
# define GREY				"\033[38;5;8m"
// # define WHITE				"\033[38;5;7m"
// # define GRAS				"\033[1m"
// # define PINK				"\033[35m"

void		p_header(void *ptr);
void		p_oct(void *ptr, size_t i);
void		p_raw(char raw[PART * 2], size_t size, void *ptr);

void		show_dump_mem(void *ptr)
{
	size_t		i[2];
	size_t		size;
	char		raw[PART * 2];

	//Verfif du pointeur
	LINE = 0;
	size = ((t_bloc*)(ptr - SIZE_HEAD))->size;
	p_header(ptr - SIZE_HEAD);
	while (LINE++ * (PART * 2) < size)
	{
		COL = 0;
		write(1, "0x", 2);
		p_posi((size_t)ptr, 16);
		while (COL < (PART * 2) && (((LINE - 1) * (PART * 2)) + COL) < size)
		{
			p_oct(ptr, COL);
			raw[COL++] = (OCT >= ' ' && OCT <= '~') ? OCT : '.';
			++ptr;
		}
		p_raw(raw, COL, ptr);
	}
}

void		p_header(void *ptr)
{
	size_t	i[2];
	t_bloc	header;

	i[0] = 0;
	header = *PTR;
	while (i[0] < 4)
	{
		COL = 0;
		write(1, "0x", 2);
		p_posi((size_t)ptr, 16);
		while (COL < (size_t[4]){
			sizeof(header.size), sizeof(header.empty),
			sizeof(header.prev), sizeof(header.next)}[i[0]])
		{
			p_oct(ptr, COL++);
			++ptr;
		}
		p_raw(, , ptr);
		++i[0];
	}
	write(1, "\n", 1);
}

void		p_oct(void *ptr, size_t i)
{
	static bool	colored;


	(i == 0) ? write(1, "  ", 2) : write(1, i == PART ? "\t" : " ", 1);
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
		(OCT % 16) > 9 ? (OCT % 16) + 'A' - 10 : (OCT % 16) + '0',
		(OCT / 16) > 9 ? (OCT / 16) + 'A' - 10 : (OCT / 16) + '0'}, 2);
}

void		p_raw(char raw[PART * 2], size_t size, void *ptr)
{
	size_t	i;

	if (!*((unsigned char*)(ptr - 1)))
		write(1, RESET, 4);
	i = 0;
	while (size + i < (PART * 2))
		write(1, size + i++ == PART ? "\t  " : "   ", 3);
	i = 0;
	while (i++ < 3)
		write(1, (char*[3]){"  |", raw, "|\n"}[i - 1],
		(size_t[3]){3, size, 2}[i - 1]);
}
