/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbernier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 14:43:26 by pbernier          #+#    #+#             */
/*   Updated: 2019/05/31 18:49:33 by rlecart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

void		*check_ptr(void *ptr);
void		*check_list(void *ptr, t_bloc *page, enum e_type type);
bool		check_corrupt(t_bloc *ptr, bool page, enum e_type type);

#define	LIST	((t_bloc*[3]){G_TINY, G_SMALL, G_LARGE})

// #define P_PTR		(size_t)ptr
// #define P_START		(size_t)page
// #define P_END		(size_t)(page + page->size);


void		free2(void *ptr)
{
	void	*start;

	//printf("1[%p]\n", ptr);
	start = check_ptr(ptr);
	//printf("2[%p]\n", ptr);

	//verif ptr
	//	verifie chasue ptr glob pour
	//	return le debut de sa data
	//  verifer si corrompu;
	//verif son type :
	// agit en consequence
}

void		*check_ptr(void *ptr)
{
	size_t			i;
	void			*start;
	t_bloc			*list;
	enum e_type		type;

	i = 0;
	start = NULL;
	while (i < 3)
	{
		list = LIST[i];
		type = ((enum e_type[3]){TINY, SMALL, LARGE})[i];
		if ((start = check_list(ptr, list, type)))
		 	return (start);
		i++;
	}
	return (error(PTR_INVALID));
}

void		*check_list(void *ptr, t_bloc *page, enum e_type type)
{
	if (!page || !check_corrupt(page, true, type))
		return (NULL);
	while (page)
	{
		//if ((size_t)page < (size_t)ptr)
		//	printf("[%p] [%p]\n", ptr, page);

		//compare voir si il est dans la page
		page = page->next;
		(void)type;
		(void)ptr;
	}
	return (NULL);
}

bool		check_corrupt(t_bloc *ptr, bool page, enum e_type type)
{
	size_t			i;
	enum e_corrupt	corrupt;

	i = ITERATOR(type);
	corrupt = CORRUPT_START;
	if ((type == TINY && (ptr->size > TINY)) ||
		(type == SMALL && (ptr->size <= TINY || ptr->size > SMALL)) ||
		(type == LARGE && (ptr->size <= SMALL || ptr->size > LARGE)))
		return (error((page) ? corrupt + i : corrupt + i + 3));


	printf("[%zu] > [%zu] \n", ptr->size,
	((size_t)(LIST[i - 1]) + S_PAGE(type) + SIZE_HEAD) - ((size_t)(ptr) + SIZE_HEAD));

	if (!page && (ptr->size >
		(((size_t)(LIST[i]) + type) - ((size_t)(ptr) + SIZE_HEAD))))
		printf("?\n");

	(void)page;
	return (1);
}
