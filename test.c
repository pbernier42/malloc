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
	t_bloc *tmp[5];
	size_t i;

	i = 0;
	tmp[0] = NULL;
	tmp[1] = NULL;
	tmp[2] = NULL;
	tmp[3] = NULL;
	tmp[4] = NULL;

	write(2, ".", 1);
	tmp[3] = realloc(tmp[1], small + 2);
	write(2, ".", 1);
	tmp[1] = realloc(tmp[2], tiny);
	write(2, ".", 1);
	tmp[2] = malloc(small);
	write(2, ".", 1);
	free(tmp[0]);
	write(2, ".", 1);
	tmp[1] = malloc(small - 10);
	write(2, ".", 1);
	tmp[1] = malloc(tiny);
	write(2, ".", 1);
	free(tmp[3]);
	write(2, ".", 1);
	tmp[2] = realloc(tmp[3], small);
	write(2, ".", 1);
	tmp[1] = malloc(tiny - 10);
	write(2, ".", 1);
	free(tmp[1]);
	write(2, ".", 1);
	free(tmp[2]);
	write(2, ".", 1);
	tmp[2] = malloc(large + 45);
	write(2, ".", 1);
	tmp[1] = malloc(tiny);
	write(2, ".", 1);
	free(tmp[0]);
	write(2, ".", 1);
	tmp[2] = realloc(tmp[3], small);
	write(2, ".", 1);
	tmp[0] = realloc(tmp[1], tiny);
	write(2, ".", 1);
	tmp[3] = malloc(500);
	write(2, ".", 1);
	tmp[0] = malloc(0);
	write(2, "2", 1);
	tmp[1] = malloc(small - 10);
	write(2, ".", 1);
	tmp[1] = malloc(tiny);
	write(2, ".", 1);
	free(tmp[0]);
	write(2, ".", 1);
	tmp[2] = realloc(tmp[3], small);
	write(2, ".", 1);
	tmp[0] = realloc(tmp[1], tiny);
	write(2, ".", 1);
	tmp[3] = malloc(500);
	write(2, ".", 1);
	free(tmp[1]);
	write(2, ".", 1);
	tmp[0] = malloc(10);
	write(2, "5", 1);
	tmp[1] = realloc(tmp[2], small);
	write(2, "6", 1);
	tmp[0] = realloc(tmp[1], small);
	write(2, "7", 1);
	printf ("\n%p\n", tmp[2]--);
	printf ("%zu\n", tmp[2]->size);
	printf ("%d\n", tmp[2]->empty);
	printf ("%p\n", tmp[2]->prev);
	printf ("%p\n", tmp[2]->next);
	tmp[2]++;
	free(tmp[2]);
	write(2, "8", 1);
	printf ("\n%p\n", tmp[2]--);
	printf ("%zu\n", tmp[2]->size);
	printf ("%d\n", tmp[2]->empty);
	printf ("%p\n", tmp[2]->prev);
	printf ("%p\n", tmp[2]->next);
	tmp[2]++;

	tmp[0] = realloc(tmp[2], small - 2);
	
	write(2, "9", 1);
	tmp[0] = realloc(tmp[1], small);
	write(2, "a", 1);
	free(tmp[2]);
	write(2, "b", 1);
	tmp[0] = realloc(tmp[2], small - 2);
	write(2, "c", 1);
	tmp[2] = malloc(small + 10);
	write(2, "d", 1);
	tmp[2] = malloc(tiny + 10);
	write(2, "e", 1);
	free(tmp[0]);
	write(2, ".", 1);
	tmp[2] = realloc(tmp[0], large);
	write(2, ".", 1);
	tmp[2] = malloc(small + 10);
	write(2, ".", 1);
	tmp[2] = malloc(tiny + 10);
	write(2, ".", 1);
	free(tmp[0]);
	write(2, ".", 1);
	tmp[2] = realloc(tmp[0], large);
	write(2, ".", 1);
	tmp[0] = malloc(large);
	write(2, "", 1);
	free(tmp[3]);
	write(2, ".", 1);
	tmp[1] = malloc(small - 10);
	write(2, ".", 1);
	free(tmp[2]);
	write(2, ".", 1);
	tmp[3] = malloc(tiny);
	write(2, ".", 1);
	free(tmp[1]);
	write(2, ".", 1);
	tmp[2] = realloc(tmp[3], small);
	write(2, "END\n", 4);
	printf("END\n");









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
