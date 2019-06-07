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
# define COLU	i[1]

void		show_dump_mem(void *ptr)
{
	size_t	i[2];
	size_t	size;

	//Verfif du pointeur
	LINE = 0;
	size = ((t_bloc*)(ptr - SIZE_HEAD))->size;
	while (LINE < (size / (PART * 2)))
	{
		COLU = 0;
		write(1, "0x", 2);
		p_posi((size_t)ptr, 16);
		//printf("%zu\n", (LINE * (PART * 2)));
		while (COLU < (PART * 2) && ((LINE * (PART * 2)) + COLU) < size)
		{
			write(1, COLU++ == PART ? "\t" : " ", 1);
			p_posi(*((size_t*)ptr), 16);
			ptr++;
		}
		write(1, "\n", 1);
		++LINE;
	}

}
