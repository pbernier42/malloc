/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbernier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 14:39:39 by pbernier          #+#    #+#             */
/*   Updated: 2019/05/17 22:21:17 by rlecart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

//# include <stdlib.h>
# include <sys/mman.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>

# include <stdio.h>

# define SIZE_HEAD			((size_t)sizeof(t_bloc))

# define T_SIZE_DATA		16
# define T_SIZE_PAGE		(getpagesize() * 2)
# define T_SIZE_BLOC		(SIZE_HEAD + T_SIZE_DATA)
# define T_SIZE_ZERO		(T_SIZE_PAGE % T_SIZE_BLOC)
# define T_NB_BLOC			(T_SIZE_PAGE / (float)T_SIZE_BLOC)

# define S_SIZE_DATA		123 //calcul allocation >= 100
# define S_SIZE_PAGE		(getpagesize() * 4)
# define S_SIZE_BLOC		(SIZE_HEAD + S_SIZE_DATA)
# define S_SIZE_ZERO		(S_SIZE_PAGE % S_SIZE_BLOC)
# define S_NB_BLOC			(S_SIZE_PAGE / (float)S_SIZE_BLOC)

# define TINY				T_SIZE_DATA
# define SMALL				S_SIZE_DATA
# define LARGE 				UINT_MAX - SIZE_HEAD//4 294 967 295

# define FL_PROT			PROT_READ | PROT_WRITE
# define FL_MAP				MAP_ANON | MAP_PRIVATE

# define PAGE				0
# define TYPE				1
# define ZERO				2
# define BLOC				3
# define ITER				4

# define CURSOR				((t_bloc*)cursor)
# define BETTER				((void*)better)

typedef struct s_type		t_type;
typedef struct s_bloc		t_bloc;

struct						s_bloc
{
	size_t					size;
	bool					empty;
	struct	s_bloc			*prev;
	struct	s_bloc			*next;
};

struct						s_type
{
	t_bloc					*tiny;
	t_bloc					*small;
	t_bloc					*large;
};

extern t_type				g_mem;

void						*malloc(size_t size);
bool						new_page(size_t size, t_bloc **page, size_t type);
t_bloc						new_bloc(size_t size, bool empty, t_bloc *prev, t_bloc *next);
void						*create_bloc(size_t size, t_bloc *page, size_t type);
t_bloc						*find_best(size_t size, t_bloc *page, size_t s_page, size_t s_min);
void						place_header(size_t size, t_bloc *better, size_t type);

void						free(void *ptr);
void						*realloc(void *ptr, size_t size);

void						show_alloc_mem();
void						print_posi(size_t number, size_t base);
void						print_adre(t_bloc **bloc);

size_t						finder(size_t size, int i);

//void 						print_define();

#endif
