/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbernier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 14:43:26 by pbernier          #+#    #+#             */
/*   Updated: 2019/05/27 22:02:39 by rlecart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

void	*where_exactly(void *cursor, size_t page_size, void *ptr)
{
	size_t	count;

	count = 0;
	while (count < page_size)
	{
		if (ptr >= cursor && ptr <= cursor + SIZE_HEAD + CURSOR->size)
			return (cursor);
		cursor += SIZE_HEAD + CURSOR->size;
		count += SIZE_HEAD + CURSOR->size;
	}
	return (NULL);
}

void	*is_here(void *ptr, t_bloc *page)
{
//	t_bloc	*prev;
	t_bloc	*islarge;
	void	*cursor;
	size_t	page_size;

	page_size = finder(page->size, PAGE);
	islarge = page;
	while (page && (cursor = page))
	{
		if (ptr >= cursor && ptr <= cursor + page_size)
			return (where_exactly(cursor, page_size, ptr));
		if ((page = page->next) == islarge)
			break ;
	}
	return (NULL);
}

void	*is_our(void *ptr)
{
	int		i;
	void	*ret;
	void	*page[4];

	i = 0;
	page[0] = T_TINY;
	page[1] = T_SMALL;
	page[2] = T_LARGE;
	page[3] = NULL;
	while (page[i] && !(ret = is_here(ptr, page[i])))
		i++;
	return (ret);
}

void	free(void *ptr)
{
	void	*cursor;
//	size_t	type;

	//bzero(ptr, size);
	//switch PROTEC
	if (ptr && (cursor = is_our(ptr)))
	{
		if (!CURSOR->empty)
		{
			//do
			//changer header
			//fusion headers
		}
	}
}
