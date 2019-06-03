/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbernier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 14:39:39 by pbernier          #+#    #+#             */
/*   Updated: 2019/05/31 18:46:24 by rlecart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <sys/mman.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>

# include <stdio.h>
# include <math.h>

# define PROTEC				0

# define SIZE_HEAD			((size_t)sizeof(t_bloc))

/*
** DATA = 0032 0096 0224 0480 0992 2016 4064 8160
**
** ALLO = 0128 0064 0032 0016 0008 0004 0002 0001 *2
** ALLO = 0256 0128 0064 0032 0016 0008 0004 0002 *4
** ALLO = 0512 0256 0128 0064 0032 0016 0008 0004 *8
*/

# define T_SIZE_DATA		32
# define T_SIZE_PAGE		(getpagesize() * 2)
# define T_SIZE_BLOC		(SIZE_HEAD + T_SIZE_DATA)
# define T_SIZE_ZERO		(T_SIZE_PAGE % T_SIZE_BLOC)
# define T_NB_BLOC			(T_SIZE_PAGE / (float)T_SIZE_BLOC)

# define S_SIZE_DATA		96
# define S_SIZE_PAGE		(getpagesize() * 4)
# define S_SIZE_BLOC		(SIZE_HEAD + S_SIZE_DATA)
# define S_SIZE_ZERO		(S_SIZE_PAGE % S_SIZE_BLOC)
# define S_NB_BLOC			(S_SIZE_PAGE / (float)S_SIZE_BLOC)

# define TINY				T_SIZE_DATA
# define SMALL				S_SIZE_DATA
# define LARGE 				UINT_MAX - SIZE_HEAD

/*
** 4 294 967 295
*/

# define T_TINY				((t_bloc*)g_mem.tiny)
# define T_SMALL			((t_bloc*)g_mem.small)
# define T_LARGE			((t_bloc*)g_mem.large)

# define G_TINY				g_mem.tiny
# define G_SMALL			g_mem.small
# define G_LARGE			g_mem.large

# define FL_PROT			PROT_READ | PROT_WRITE
# define FL_MAP				MAP_ANON | MAP_PRIVATE

# define S_PAGE(size)		finder(size, 0)
# define TYPE(size)			finder(size, 1)
# define S_ZERO(size)		finder(size, 2)
# define S_BLOC_MIN(size)	finder(size, 3)
# define ITERATOR(size)		finder(size, 4)

# define CURSOR				((t_bloc*)cursor)
# define BETTER				((void*)better)
# define PTR				((t_bloc*)ptr)

# define UNKNOWN_ERROR		0
# define MUNMAP_FAIL		-1
# define PTR_INVALID		2
# define PTR_CORRUT			3


typedef struct s_type		t_type;
typedef struct s_bloc		t_bloc;

struct						s_bloc
{
	size_t					size;
	bool					empty;
	struct s_bloc			*prev;
	struct s_bloc			*next;
};

struct						s_type
{
	t_bloc					*tiny;
	t_bloc					*small;
	t_bloc					*large;
};

extern t_type				g_mem;

void						*malloc(size_t size);
bool						new_page(size_t s_page, t_bloc **page, size_t type);
t_bloc						new_bloc(size_t size, bool empty, t_bloc *prev,
								t_bloc *next);
void						*create_bloc(size_t size, t_bloc *page,
								size_t type);
t_bloc						*find_best(size_t size, t_bloc *page, size_t s_page,
								size_t s_min);
void						place_header(size_t size, t_bloc *better,
								size_t type, bool realloc);

void						free(void *ptr);
bool						delete_page(t_bloc *prev, t_bloc *cursor,
								t_bloc *next);
bool						do_i_have_to_delete_page(void *cursor,
								size_t page_size);

void						*realloc(void *ptr, size_t size);
bool						move_bloc(void *ptr, size_t size, size_t type);
void						*reset(void *ptr, size_t size);

void						show_alloc_mem();

void						p_posi(size_t number, size_t base);
void						p_line(char **line, size_t *len, size_t number,
								size_t base);
size_t						p_bloc(t_bloc *bloc, size_t s_page, size_t octets);

size_t						finder(size_t size, size_t i);
void						*error(int error);

#endif
