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

void		p_oct(void *ptr);
void		p_raw(char raw[PART * 2], size_t size);

void		show_dump_mem(void *ptr)
{
	size_t	i[2];
	size_t	size;
	char	raw[PART * 2];

	//Verfif du pointeur
	LINE = 0;
	size = ((t_bloc*)(ptr - SIZE_HEAD))->size;
	while (LINE * (PART * 2) < size)
	{
		COL = 0;
		write(1, "0x", 2);
		p_posi((size_t)ptr, 16);
		while (COL < (PART * 2) && ((LINE * (PART * 2)) + COL) < size)
		{
			(COL == 0) ?
				write(1, "  ", 2) :
				write(1, COL == PART ? "\t" : " ", 1);
			p_oct(ptr);
			raw[COL++] = (OCT >= ' ' && OCT <= '~') ? OCT : '.';
			++ptr;
		}
		p_raw(raw, COL);
		++LINE;
	}
}

void		p_oct(void *ptr)
{
	write(1, (char[2]){
		(OCT % 16) > 9 ? (OCT % 16) + 'A' - 10 : (OCT % 16) + '0',
		(OCT / 16) > 9 ? (OCT / 16) + 'A' - 10 : (OCT / 16) + '0'}, 2);
}

void		p_raw(char raw[PART * 2], size_t size)
{
	size_t	i;

	i = 0;
	while (size + i < (PART * 2))
		write(1, size + i++ == PART ? "\t  " : "   ", 3);
	i = 0;
	while (i++ < 3)
		write(1, (char*[3]){"  |", raw, "|\n"}[i - 1],
		(size_t[3]){3, size, 2}[i - 1]);
}
