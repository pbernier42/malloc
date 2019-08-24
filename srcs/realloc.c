/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbernier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 14:43:32 by pbernier          #+#    #+#             */
/*   Updated: 2019/05/31 18:15:34 by rlecart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

t_type		g_mem;

void		*realloc(void *ptr, size_t size)
{
	t_posi		posi;
	size_t		align[2];
	enum e_type	type[2];
	size_t		s_prev;

	if (!ptr || !size)
		return (malloc(size));
	posi = check_ptr(ptr, ft_realloc);
	if (!P_BLOC || !P_PAGE)
		return (NULL);
	if (P_BLOC->size == size && !(G_FONCTION = ft_null))
		return (BLOC + SIZE_HEAD);
	s_prev = P_BLOC->size;
	TYPE_NEW = TYPE(size);
	TYPE_OLD = TYPE(s_prev);
	if (!move_bloc(posi, size, type))
		return (reset(posi, s_prev, size, TYPE_OLD));
	AS_OLD = S_PAGE(s_prev);
	if (TYPE_NEW == large && AS_OLD > (AS_NEW = S_PAGE(size)))
		if (munmap(BLOC + AS_NEW, AS_OLD - AS_NEW) == MUNMAP_FAIL)
			return (ft_error(munmap_fail));
	place_header(size, posi, TYPE_NEW, ft_realloc);
	add_histo((t_hist){true, ft_realloc, {BLOC + SIZE_HEAD, NULL},
		{s_prev, size}});
	return (BLOC + SIZE_HEAD);
}

bool		move_bloc(t_posi posi, size_t size, enum e_type type[2])
{
	size_t	s_page;
	size_t	align[3];

	if (!P_BLOC || (TYPE_NEW != TYPE_OLD))
		return (false);
	AS_NEW = A_SIZE(size);
	AS_MIN = A_SIZE(S_BLOC_MIN(TYPE_OLD));
	AS_OLD = A_SIZE(P_BLOC->size);
	s_page = S_PAGE(TYPE_OLD);
	if (TYPE_NEW == large)
		return (AS_OLD > AS_NEW ? true : false);
	if (((size_t)PAGE + s_page > ((size_t)BLOC + SIZE_HEAD + AS_OLD)
		&& ((t_bloc *)(BLOC + SIZE_HEAD + AS_OLD))->empty))
		AS_OLD += SIZE_HEAD
		+ A_SIZE(((t_bloc *)(BLOC + SIZE_HEAD + AS_OLD))->size);
	if (AS_OLD > AS_NEW && AS_OLD > (SIZE_HEAD + AS_MIN + AS_NEW))
		P_BLOC->size = AS_OLD;
	else if (AS_OLD != AS_NEW)
		return (false);
	return (true);
}

void		*reset(t_posi posi, size_t s_prev, size_t size, enum e_type type)
{
	void	*prev;
	void	*ret;

	prev = BLOC;
	ret = malloc(size);
	copy_data(ret, BLOC + SIZE_HEAD, ((size_t[2]){size, s_prev}));
	delete_bloc(posi, type);
	add_histo((t_hist){true, ft_realloc, {prev, ret != prev ? ret : NULL},
		{s_prev, ret ? ((t_bloc*)(ret - SIZE_HEAD))->size : 0}});
	return (ret);
}

void		copy_data(void *new, void *data, size_t len[2])
{
	size_t	i;
	size_t	limit;

	i = 0;
	limit = S_NEW < S_DATA ? S_NEW : S_DATA;
	while (i++ < limit)
		NEW[i - 1] = DATA[i - 1];
}
