/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbernier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 13:15:35 by pbernier          #+#    #+#             */
/*   Updated: 2019/06/07 13:15:36 by pbernier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

t_type		g_mem;

void		show_histo_mem(void)
{
	size_t	size;
	size_t	end;

	if (!HISTORY)
		return ;
	size = (!G_HISTO[LAST].full) ? 0 : LAST;
	end = (!G_HISTO[LAST].full) ? LAST : LAST + H_NB_BLOC;
	if (LAST)
		write(1, "\n", 1);
	while (size < end)
		p_histo(G_HISTO[(size++ % H_NB_BLOC)]);
	if (LAST)
		write(1, "\n", 1);
}

void		p_histo(t_hist bloc)
{
	write(1, GREY, 9);
	write(1, ((char*[3]){"[Malloc]\n", "[Realloc]\n",
		"[Free]\n"})[bloc.fonction - 1],
			((size_t[3]){9, 10, 7})[bloc.fonction - 1]);
	write(1, RESET, 4);
	p_adress(bloc.ptr[0], bloc.size[0], false);
	if (bloc.fonction == ft_realloc)
		p_adress(bloc.ptr[1], bloc.size[1], true);
	write(1, "\n", 1);
}

void		p_adress(void *ptr, size_t size, bool second)
{
	(second) ? write(1, "\t>\t", 3) : write(1, "0x", 2);
	if (ptr)
	{
		if (second)
			write(1, "0x", 2);
		p_posi((size_t)ptr, 16);
		write(1, " - ", 3);
	}
	p_posi(size, 10);
}

bool		add_histo(t_hist bloc)
{
	g_mem.fonction = ft_null;
	if (!HISTORY)
		return (true);
	G_HISTO[LAST] = bloc;
	LAST += (LAST != (H_NB_BLOC - 1)) ? 1 : -(H_NB_BLOC - 1);
	return (true);
}
