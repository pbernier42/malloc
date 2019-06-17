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

void		show_histo_mem()
{
	size_t	size;
	size_t	end;

	if (!HISTORY)
		return ;
	size = (!G_HISTO[LAST].full) ? 0 : LAST;
	end = (!G_HISTO[LAST].full) ? LAST : LAST - 1;

	printf("[%zu] [%zu][%zu]\n", LAST, size, end);

	while ((size % H_NB_BLOC) != end)
		p_histo(G_HISTO[size++]);
}

void		p_histo(t_hist bloc)
{
	write(1, ((char*[3]){
		"[Malloc]\n",
		"[Realloc]\n",
		"[Free]\n"})[bloc.fonction],
		((size_t[3]){9, 10, 7})[bloc.fonction]);

	(void)bloc;
}

bool		add_histo(t_hist bloc)
{
	//printf("ADD_HISTO[%zu]\n", LAST);
	G_HISTO[LAST] = bloc;
	LAST += (LAST != (H_NB_BLOC - 1)) ? 1 : -(H_NB_BLOC - 1);
	return (true);
}
