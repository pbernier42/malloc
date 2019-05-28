/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbernier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 14:43:26 by pbernier          #+#    #+#             */
/*   Updated: 2019/05/28 21:08:51 by rlecart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

void	*where_exactly(void *cursor, size_t page_size, void *ptr)
{
	void	*prev;
	void	*next;
	size_t	count;

	count = 0;
	prev = NULL;
	while (count < page_size)
	{
		next = cursor + SIZE_HEAD + CURSOR->size;
		if (ptr >= cursor && ptr <= cursor + SIZE_HEAD + CURSOR->size)
		{
			if (count + SIZE_HEAD + CURSOR->size < page_size && next && ((t_bloc*)next)->empty)
				CURSOR->size += ((t_bloc*)next)->size + SIZE_HEAD;
			CURSOR->empty = true;
			if (prev && ((t_bloc*)prev)->empty)
				((t_bloc*)prev)->size += CURSOR->size + SIZE_HEAD;
			return (cursor);
		}
		prev = cursor;
		cursor += SIZE_HEAD + CURSOR->size;
		count += SIZE_HEAD + CURSOR->size;
	}
	return (NULL);
}

bool	delete_page(t_bloc *prev, t_bloc *cursor, t_bloc *next, size_t page_size)
{
	if (prev)
		((t_bloc*)prev)->next = next;
	if (next)
		((t_bloc*)next)->prev = prev;
	if ((munmap(cursor, CURSOR->size + SIZE_HEAD)))
			return (false);
	return (true);
}

bool	do_i_have_to_delete_page(void *cursor, size_t page_size, t_bloc *page, t_bloc *start)
{
	if (cursor && CURSOR->empty && CURSOR->size + SIZE_HEAD >= page_size)
		return (true);
	return (false);
}

int		is_here(void *ptr, t_bloc *page)
{
	t_bloc	*prev;
	t_bloc	*next;
	t_bloc	*islarge;
	void	*cursor;
	size_t	page_size;

	page_size = finder(page->size, PAGE);
	islarge = page;
	prev = NULL;
	while (page && (cursor = page))
	{
		if (ptr >= cursor && ptr <= cursor + page_size)
		{
			if (!(cursor = where_exactly(cursor, page_size, ptr)))
				return (2);
			if (do_i_have_to_delete_page(cursor, page_size, page, islarge))
				return (!(delete_page(prev, cursor, CURSOR->next, page_size)) ? -1 : 0);
		}
		prev = cursor;
		if ((page = page->next) == islarge) //theoriquement toujours fausse (a cause du return des le delete_page
			break ;
	}
	return (1);
}

bool	is_our(void *ptr)
{
	int		i;
	bool	ret;
	void	*page[4];

	i = 0;
	page[0] = T_TINY;
	page[1] = T_SMALL;
	page[2] = T_LARGE;
	page[3] = NULL;
	while (page[i] && !(ret = is_here(ptr, page[i])))// -1 pas reussi a munmap, 1 ITSOK, 0 not here
		i++;
	return (ret);
}

//bzero(ptr, size);
//switch PROTEC
//retrouver un pointeur corrompu (si prev existe alors cursor = prev + SIZE_HEAD + prev->size)
//si prev n'existe pas alors c'est le premier octet de la page
//
void	free(void *ptr)
{
	int		ret;
	if (ptr && (ret = is_our(ptr)))
	{
		if (ret == -1)
			error("PAS REUSSI A MUNMAP");
		else if (ret == 1)
			error("PTR PAS A NOUS");
		else if (ret == 2)
			error("PTR A NOUS MAIS PROBABLEMENT CORROMPU");
	}
}
