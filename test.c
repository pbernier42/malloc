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

#define GG	5000

int			main(void)
{

	t_bloc *tmp[GG];
	//size_t i[2];


	tmp[0] = malloc(small + 10);
	tmp[1] = malloc(small + 10);
	tmp[2] = malloc(small + 10);
	tmp[3] = malloc(small + 10);

	free(tmp[3]);
	tmp[3] = malloc(small + 10);

	// printf("1[%p][%zu][%d]\n1[%p]prev\n1[%p]next\n\n", G_LARGE, G_LARGE->size,
	// 	G_LARGE->empty, G_LARGE->prev, G_LARGE->next);
	show_alloc_mem();
	show_dump_mem(tmp[2]);
	show_histo_mem();




	return(0);



	//show_dump_mem(tmp[0]);
	tmp[0] = malloc(large -10);
	//show_dump_mem(tmp[0]);

	free(tmp[0]);
	//free(tmp[0]);

	//tmp[1] = realloc(tmp[0], 10);
	return(0);
	show_alloc_mem();
	show_dump_mem(tmp[1]);
	show_histo_mem();

	// while (i[1] <= (4500))
	// {
	// 	if (i[1] >= 500 && i[1] <= 4000)
	// 		free(tmp[i[1]]);
	// 	i[1]++;
	// }

	return(0);

	--tmp[60];

	t_bloc *t = tmp[60];
	printf("%zu - %d - %p - %p\n", t->size, t->empty, t->prev, t->next);

	//show_dump_mem(tmp[50]);
	show_dump_mem(tmp[60]);
	//show_dump_mem(tmp[61]);




	return (0);


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
	free(tmp[2]);
	write(2, "8", 1);
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
	write(2, "2", 1);

	//tmp[2] = realloc(tmp[0], large);
	//write(2, ".", 1);
	//tmp[0] = malloc(large);
	//write(2, "", 1);
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
