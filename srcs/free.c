/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbernier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 14:43:26 by pbernier          #+#    #+#             */
/*   Updated: 2019/05/27 20:22:52 by rlecart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

void	*is_our(void *ptr)
{
	int		i;
	void	*ret;
	void	*page[4];

	//page[0] = &;
	return (ret);
}

void	*find_true(void *ptr)
{
	void	*ret;

	return (ret);
}

void	free(void *ptr)
{
	void	*cursor;
	size_t	type;

	//bzero(ptr, size);
	if (ptr && (cursor = is_our(ptr)))
	{
		if (!CURSOR->empty)
		{
		}
	}
}
