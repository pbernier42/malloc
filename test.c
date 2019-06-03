/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbernier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 17:30:39 by pbernier          #+#    #+#             */
/*   Updated: 2019/05/06 17:30:40 by pbernier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <malloc.h>

#define TB_PTR			((t_bloc*)(ptr - SIZE_HEAD))
//#define GRIS			printf("\033[38;5;8m")
//#define RESET			printf("\033[0m")

void		test_realloc();
void		my_test();
void		print_all();

int			main(void)
{
	//test_realloc();
	my_test();
	//print_all();
	return (0);
}

void		my_test()
{
	void 	*ptr;

	//(LARGE : Plus grand qu'avant)
	printf("(LARGE : Plus grand qu'avant)\n");
	ptr = malloc(SMALL + 50);
	printf("size : [%lu] empty : [%s]\nptr = [%p]\n", TB_PTR->size, TB_PTR->empty == true ? "VIDE" : "PLEIN", TB_PTR);
	ptr = realloc(ptr, 500);
	printf("size : [%lu] empty : [%s]\nptr = [%p]\n", TB_PTR->size, TB_PTR->empty == true ? "VIDE" : "PLEIN", TB_PTR);
	printf("\n");
	show_alloc_mem();
	printf("\n");
	print_all();
	(void)ptr;
}

void		test_realloc()
{
	void	*ptr = NULL;


	//(Size ne change pas)
	printf("(Size ne change pas)\n");
	ptr = malloc(TINY);
	printf("size : [%lu] empty : [%s]\nptr = [%p]\n", TB_PTR->size, TB_PTR->empty == true ? "VIDE" : "PLEIN", TB_PTR);
	ptr = realloc(ptr, TINY);
	printf("size : [%lu] empty : [%s]\nptr = [%p]\n", TB_PTR->size, TB_PTR->empty == true ? "VIDE" : "PLEIN", TB_PTR);
	show_alloc_mem();
	printf("\n");

	//(Size fait changer de type)
	printf("(Size fait changer de type)\n");
	malloc(SMALL);
	malloc(SMALL + 10);
	ptr = malloc(SMALL);
	printf("size : [%lu] empty : [%s]\nptr = [%p]\n", TB_PTR->size, TB_PTR->empty == true ? "VIDE" : "PLEIN", TB_PTR);
	ptr = realloc(ptr, TINY);
	printf("size : [%lu] empty : [%s]\nptr = [%p]\n", TB_PTR->size, TB_PTR->empty == true ? "VIDE" : "PLEIN", TB_PTR);
	show_alloc_mem();
	printf("\n");

	//(LARGE : Plus grand qu'avant)
	printf("(LARGE : Plus grand qu'avant)\n");
	ptr = malloc(SMALL + 50);
	printf("size : [%lu] empty : [%s]\nptr = [%p]\n", TB_PTR->size, TB_PTR->empty == true ? "VIDE" : "PLEIN", TB_PTR);
	//Plus le chiffre "50" est grand plus il creer des pages large vide
	ptr = realloc(ptr, TB_PTR->size + 50);
	printf("size : [%lu] empty : [%s]\nptr = [%p]\n", TB_PTR->size, TB_PTR->empty == true ? "VIDE" : "PLEIN", TB_PTR);
	show_alloc_mem();
	printf("\n");


	//(SMALL : Plus grand qu'avant)
	printf("(SMALL : Plus grand qu'avant)\n");
	malloc(TINY + 9);
	malloc(TINY + 9);
	ptr = malloc(TINY + 10);
	printf("size : [%lu] empty : [%s]\nptr = [%p]\n", TB_PTR->size, TB_PTR->empty == true ? "VIDE" : "PLEIN", TB_PTR);
	ptr = realloc(ptr, TB_PTR->size + 10);
	printf("size : [%lu] empty : [%s]\nptr = [%p]\n", TB_PTR->size, TB_PTR->empty == true ? "VIDE" : "PLEIN", TB_PTR);
	show_alloc_mem();
	printf("\n");
	print_all();

	//(SMALL : Plus grand qu'avant) (next occupé)
	//(SMALL : Plus grand qu'avant) (tout au bout)
	//(LARGE : Plus petit qu'avant)
	//(SMALL : Plus petit qu'avant)
	//(SMALL : Plus petit qu'avant) (Pas de place)

}

void		print_all()
{
	t_bloc	*page;
	size_t	i;
	size_t	s_page;
	void	*cursor;
	size_t	parsed;

	i = 0;
	while (i < 3)
		if ((page = ((t_bloc*[4]){G_TINY, G_SMALL, G_LARGE, NULL})[i++]))
		{
			printf("[%s]	: [%p]\n", ((char*[3]){"TINY", "SMALL", "LARGE"})[i - 1], page);
			if (page == G_LARGE)
				page = page->next;
			while ((page))
			{
				cursor = page;
				parsed = 0;
				s_page = S_PAGE(page->size);
				while (parsed < s_page)
				{
					printf("startH	: [%p]\nstartD	: [%p]\nsize	: [%zu]\nempty	: [%s]\nprev	: [%p]\nnext	: [%p]\nend	: [%p]\n\n",
					cursor, (cursor + SIZE_HEAD), CURSOR->size, CURSOR->empty == true ? "VIDE" : "PLEIN", CURSOR->prev, CURSOR->next, (cursor + CURSOR->size + SIZE_HEAD));
					parsed += CURSOR->size + SIZE_HEAD;
					cursor += CURSOR->size + SIZE_HEAD;
				}
				page = (page == G_LARGE) ? NULL : page->next;
			}
			printf("\n");
		}
}
