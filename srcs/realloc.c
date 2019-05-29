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

void	*realloc(void *ptr, size_t size)
{
	size_t	type;
	void	*cursor;
	size_t	s_page;
	//Verifier pointeur

	///#place au debut header
	ptr -= SIZE_HEAD;
	///#pas de changement a faire
	if (PTR->size == size)
		return (ptr);
	///#si la size = 0 malloc s'en occupe
	type = finder(size, TYPE);
	///#si ca le fait changer de type ou
	///#(LARGE) si size > a avant, free et malloc
	///#(TINY/SMALL) pas le place de couper
	if (!ptr ||
		type != finder(PTR->size, TYPE) ||
		(type == LARGE && PTR->size < size) ||
		!(type != LARGE && (PTR->size - size) > (SIZE_HEAD + finder(PTR->size, BLOC))))
		return (move_bloc(ptr, size));
	///#(LARGE) si size < a avant, free ce qu'on veut plus
	if (type == LARGE && PTR->size > size)
		if (munmap(ptr + SIZE_HEAD + size, PTR->size - size) == -1);
			return (NULL);//verbos
	///#(TINY/SMALL) si size < a avant et que le reste utilisable (réduire taille)
	///#(LARGE) changement dela valeur de size
	if (PTR->size > size)
		place_header(size, ptr, type);
	///#(TINY/SMALL) si size > a avant et que le suivant peut l'aceillier
	else if (type != LARGE && PTR->size < size)
	{
		s_page = inder(PTR->size, PAGE);
		cursor = (type == TINY) ? G_TINY : G_SMALL;
		while (!(ptr > cursor && ptr < (cursor + page))
			CURSOR = CURSOR->next;
		if (((ptr + SIZE_HEAD + PTR->SIZE) == cursor + s_page)) // ##
			return (move_bloc(ptr, size));
			
	}
	return (ptr);
}

void	*move_bloc(void *ptr, size_t size)
{
	free(ptr);
	return (malloc(size));
}
