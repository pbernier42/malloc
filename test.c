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

int			main(void)
{
	void *tmp = NULL;


	// malloc(10);
	// tmp = malloc(11);
	// //tmp = malloc(small + 50);
	// free2(tmp);
	// free2(tmp);
	// free2(tmp);
	// realloc(tmp, 10);

	//FAUX
	free2(tmp);
	tmp = malloc(6545612);
	realloc(tmp, small);
	malloc(small + 50);
	malloc(2);
	malloc(small + 50);
	free2(tmp);
	malloc(small - 3);



	show_histo_mem();
	show_alloc_mem();
	return (0);
}

void		my_test()
{
	void 	*ptr;

	//(large : Plus grand qu'avant)
	printf("(large : Plus grand qu'avant)\n");
	ptr = malloc(small + 50);
	printf("size : [%lu] empty : [%s]\nptr = [%p]\n", TB_PTR->size, TB_PTR->empty == true ? "VIDE" : "PLEIN", TB_PTR);
	ptr = realloc(ptr, 500);
	printf("size : [%lu] empty : [%s]\nptr = [%p]\n", TB_PTR->size, TB_PTR->empty == true ? "VIDE" : "PLEIN", TB_PTR);
	printf("\n");
	show_alloc_mem();
	printf("\n");
	(void)ptr;
}

void		test_realloc()
{
	void	*ptr = NULL;


	//(Size ne change pas)
	printf("(Size ne change pas)\n");
	ptr = malloc(tiny);
	printf("size : [%lu] empty : [%s]\nptr = [%p]\n", TB_PTR->size, TB_PTR->empty == true ? "VIDE" : "PLEIN", TB_PTR);
	ptr = realloc(ptr, tiny);
	printf("size : [%lu] empty : [%s]\nptr = [%p]\n", TB_PTR->size, TB_PTR->empty == true ? "VIDE" : "PLEIN", TB_PTR);
	show_alloc_mem();
	printf("\n");

	//(Size fait changer de type)
	printf("(Size fait changer de type)\n");
	malloc(small);
	malloc(small + 10);
	ptr = malloc(small);
	printf("size : [%lu] empty : [%s]\nptr = [%p]\n", TB_PTR->size, TB_PTR->empty == true ? "VIDE" : "PLEIN", TB_PTR);
	ptr = realloc(ptr, tiny);
	printf("size : [%lu] empty : [%s]\nptr = [%p]\n", TB_PTR->size, TB_PTR->empty == true ? "VIDE" : "PLEIN", TB_PTR);
	show_alloc_mem();
	printf("\n");

	//(large : Plus grand qu'avant)
	printf("(large : Plus grand qu'avant)\n");
	ptr = malloc(small + 50);
	printf("size : [%lu] empty : [%s]\nptr = [%p]\n", TB_PTR->size, TB_PTR->empty == true ? "VIDE" : "PLEIN", TB_PTR);
	//Plus le chiffre "50" est grand plus il creer des pages large vide
	ptr = realloc(ptr, TB_PTR->size + 50);
	printf("size : [%lu] empty : [%s]\nptr = [%p]\n", TB_PTR->size, TB_PTR->empty == true ? "VIDE" : "PLEIN", TB_PTR);
	show_alloc_mem();
	printf("\n");


	//(small : Plus grand qu'avant)
	printf("(small : Plus grand qu'avant)\n");
	malloc(tiny + 9);
	malloc(tiny + 9);
	ptr = malloc(tiny + 10);
	printf("size : [%lu] empty : [%s]\nptr = [%p]\n", TB_PTR->size, TB_PTR->empty == true ? "VIDE" : "PLEIN", TB_PTR);
	ptr = realloc(ptr, TB_PTR->size + 10);
	printf("size : [%lu] empty : [%s]\nptr = [%p]\n", TB_PTR->size, TB_PTR->empty == true ? "VIDE" : "PLEIN", TB_PTR);
	show_alloc_mem();
	printf("\n");

	//(small : Plus grand qu'avant) (next occupé)
	//(small : Plus grand qu'avant) (tout au bout)
	//(large : Plus petit qu'avant)
	//(small : Plus petit qu'avant)
	//(small : Plus petit qu'avant) (Pas de place)

}
