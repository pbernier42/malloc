/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbernier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 14:43:32 by pbernier          #+#    #+#             */
/*   Updated: 2019/05/06 14:43:33 by pbernier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

void		*realloc(void *ptr, size_t size)
{
	size_t	type;

	//Verifier pointeur

	ptr -= SIZE_HEAD;
	if (PTR->size == size)
		return (ptr + SIZE_HEAD);
	type = TYPE(size);
	if (!move_bloc(ptr, size, type))
		return (reset(ptr + SIZE_HEAD, size));
	if (type == LARGE && PTR->size > size)
		if (munmap(ptr + SIZE_HEAD + size, PTR->size - size) == -1)
			return (NULL);//verbos
	place_header(size, ptr, type);
	return (ptr + SIZE_HEAD);
}

bool		move_bloc(void *ptr, size_t size, size_t type)
{
	size_t	s_min;
	size_t	s_page;
	void	*cursor;

	s_min = S_BLOC_MIN(PTR->size);
	if (!ptr ||
		type != TYPE(PTR->size) ||
		(type == LARGE && PTR->size < size) ||
		!(type != LARGE && PTR->size > size && (PTR->size - size) > (SIZE_HEAD + s_min)))
		return (false);
	s_page = S_PAGE(PTR->size);
	cursor = (type == TINY) ? G_TINY : G_SMALL;
	while (!(ptr > cursor && ptr < (cursor + s_page)))
		cursor = CURSOR->next;
	if (((ptr + SIZE_HEAD + PTR->size) == cursor + s_page) ||
		!(((t_bloc*)(ptr + SIZE_HEAD + PTR->size))->empty) ||
		!(PTR->size + ((t_bloc*)(ptr + SIZE_HEAD + PTR->size))->size > size + s_min))
		return (false);
	return (true);
}

void	*reset(void *ptr, size_t size)
{
	printf("\033[31m[WARNING]\033[0m no free\n");
	//free(ptr);
	(void)ptr;
	return (malloc(size));
}
