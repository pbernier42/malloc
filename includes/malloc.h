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

# define PROTECTED			true
# define HISTORY			true

# define SIZE_HEAD			((size_t)sizeof(t_bloc))

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

# define T_TINY				((t_bloc*)g_mem.tiny)
# define T_SMALL			((t_bloc*)g_mem.small)
# define T_LARGE			((t_bloc*)g_mem.large)

# define H_SIZE_HIST		((size_t)sizeof(t_hist))
# define H_NB_BLOC			100
# define H_SIZE_PAGE		(H_SIZE_HIST * H_NB_BLOC)

# define G_TINY				g_mem.tiny
# define G_SMALL			g_mem.small
# define G_LARGE			g_mem.large
# define G_HISTO			g_mem.histo

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

# define MUNMAP_FAIL		-1

enum						e_error
{
	ERROR_START,
	UNKNOWN_ERROR = 0,
	munmap_fail	= 1,
	PTR_INVALID = 2,
	// PTR_CORRUPT = 3,
	CORRUPT_START = 3,
	PAGE_SIZE_TINY,
	PAGE_SIZE_SMALL,
	PAGE_SIZE_LARGE,
	BLOC_SIZE_TINY,
	BLOC_SIZE_SMALL,
	BLOC_SIZE_LARGE,
	PAGE_PTR_TINY,
	PAGE_PTR_SMALL,
	BLOC_PTR_LARGE,
	EMPTY_LARGE,
	BLOC_NOT_FOUND,
	ERROR_END
};

// struct						s_bloc
// {
// 	size_t					size;
// 	bool					empty;
// 	struct s_bloc			*prev;
// 	struct s_bloc			*next;
// };

# define RESET				"\033[0m"
# define GREY				"\033[38;5;8m"

# define PART				8
# define LINE				i[0]
# define I					i[0]
# define COL				i[1]
# define OCT				*((unsigned char*)ptr)
# define LAST				g_mem.hist_last

typedef struct s_type		t_type;
typedef struct s_bloc		t_bloc;
typedef struct s_hist		t_hist;
typedef struct s_hist		t_hist;

extern t_type				g_mem;

enum						e_fonction
{
   FT_NULL,
   FT_MALLOC,
   FT_REALLOC,
   FT_FREE
};

struct						s_hist
{
	bool					full;
	enum e_fonction			fonction;
	void					*ptr[2];
	size_t					size[2];
};

struct						s_bloc
{
	size_t					size;
	bool					empty;
	struct s_bloc			*prev;
	struct s_bloc			*next;
};

enum						e_type
{
   TINY = T_SIZE_DATA,
   SMALL = S_SIZE_DATA,
   LARGE = (UINT_MAX - SIZE_HEAD)
};

struct						s_type
{
	t_bloc					*tiny;
	t_bloc					*small;
	t_bloc					*large;
	size_t					hist_last;
	t_hist					histo[H_NB_BLOC];
	//enum e_fonction 		fonction; 
};

void	free2(void *ptr);

void						*malloc(size_t size);
bool						new_page(size_t s_page, t_bloc **page,
								enum e_type type);
void						*create_bloc(size_t size, t_bloc *page,
								enum e_type type);
t_bloc						*find_best(size_t size, t_bloc *page, size_t s_page,
								size_t s_min);
void						place_header(size_t size, t_bloc *better,
								enum e_type type, enum e_fonction fonction);

void						free(void *ptr);
bool						delete_page(t_bloc *prev, t_bloc *cursor,
								t_bloc *next);
bool						do_i_have_to_delete_page(void *cursor,
								size_t page_size);

void						*realloc(void *ptr, size_t size);
bool						move_bloc(void *ptr, size_t size, enum e_type type);
void						*reset(void *ptr, size_t size);

void						show_alloc_mem();
void						p_posi(size_t number, size_t base);
void						p_line(char **line, size_t *len, size_t number,
								size_t base);
size_t						p_bloc(t_bloc *bloc, size_t s_page, size_t octets);

void						show_dump_mem(void *ptr);
void						p_dump(void *ptr, t_bloc *header, size_t size,
								bool data);
void						p_head(size_t printed, size_t number, size_t base);
void						p_oct(void *ptr, size_t i);
void						p_raw(char raw[PART * 2], size_t size,
								t_bloc *header, void *ptr);

void						show_histo_mem();
bool						add_histo(t_hist bloc);
void						p_histo(t_hist bloc);
void						p_adress(void *ptr, size_t size, bool second);

size_t						finder(size_t size, size_t i);
void						*error(int error);

#endif
