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

# define HISTORY			true
# define PRINT_ERROR		false

# define SIZE_HEAD			((size_t)sizeof(t_bloc))
# define GPS				getpagesize()

# define T_SIZE_DATA		480
# define T_SIZE_PAGE		(GPS * 13)
# define T_SIZE_BLOC		(SIZE_HEAD + T_SIZE_DATA)
# define T_SIZE_ZERO		(T_SIZE_PAGE % T_SIZE_BLOC)
# define T_NB_BLOC			(T_SIZE_PAGE / (float)T_SIZE_BLOC)

# define S_SIZE_DATA		992
# define S_SIZE_PAGE		(GPS * 25)
# define S_SIZE_BLOC		(SIZE_HEAD + S_SIZE_DATA)
# define S_SIZE_ZERO		(S_SIZE_PAGE % S_SIZE_BLOC)
# define S_NB_BLOC			(S_SIZE_PAGE / (float)S_SIZE_BLOC)

# define L_SIZE_PAGE(size)	L_SIZE_BLOC + A_ZERO(L_SIZE_BLOC, GPS)
# define L_SIZE_BLOC		(size + SIZE_HEAD)

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
# define G_FONCTION			g_mem.fonction
# define G_BUFF				g_mem.buff

# define P_BLOC				posi.bloc
# define P_PAGE				posi.page
# define P_NEW				posi.bloc
# define P_START			posi.page

# define BLOC				((void*)P_BLOC)
# define PAGE				((void*)P_PAGE)
# define P_NULL				((t_posi){NULL, NULL})

# define TYPE_OLD			type[0]
# define TYPE_NEW			type[1]

# define FL_PROT			PROT_READ | PROT_WRITE | PROT_EXEC
# define FL_MAP				MAP_ANON | MAP_PRIVATE

# define AS_OLD				align[0]
# define AS_MIN				align[2]

# define AS_CUR				align[0]
# define AS_NEW				align[1]
# define AS_BET				align[2]

# define AZ_CUR				A_ZERO(CURSOR->size, 16)
# define AZ_BET				A_ZERO(P_BLOC->size, 16)

# define A_NB				16
# define A_SIZE(size)		(size + A_ZERO(size, A_NB))
# define A_ZERO(size, a_nb)	(!(size % a_nb) ? 0 : (a_nb - (size % a_nb)))

# define S_PAGE(size)		finder(size, 0)
# define TYPE(size)			finder(size, 1)
# define S_ZERO(size)		finder(size, 2)
# define S_BLOC_MIN(size)	finder(size, 3)
# define ITERATOR(size)		finder(size, 4)

# define CURSOR				((t_bloc*)cursor)

# define MUNMAP_FAIL		-1

enum						e_error
{
	error_start = -1,
	unknown_error = 0,
	munmap_fail = 1,
	ptr_invalid = 2,
	corrupt_start = 3,
	page_size_tiny,
	page_size_small,
	page_size_large,
	bloc_size_tiny,
	bloc_size_small,
	bloc_size_large,
	page_ptr_tiny,
	page_ptr_small,
	bloc_ptr_large,
	empty_large,
	empty_tiny,
	empty_small,
	bloc_not_found,
	bloc_align_tiny,
	bloc_align_small,
	bloc_align_large,
	page_align_tiny,
	page_align_small,
	page_align_large,
	error_end
};

# define RESET				"\033[0m"
# define GREY				"\033[38;5;8m"

# define PART				8
# define LINE				i[0]
# define I					i[0]
# define COL				i[1]
# define OCT				*((unsigned char*)ptr)
# define LAST				g_mem.hist_last

# define LIST				((t_bloc*[3]){G_TINY, G_SMALL, G_LARGE})
# define G_LIST				((t_bloc**[3]){&G_TINY, &G_SMALL, &G_LARGE})
# define PAGE_START			p_limit[0]
# define PAGE_END			p_limit[1]
# define BLOC_START			b_limit[0]
# define BLOC_END			b_limit[1]
# define NEXT_BLOC			((t_bloc*)(cursor + SIZE_HEAD + as_cur))
# define CURS_START			p_limit[0]

# define NEW				((unsigned char *)new)
# define DATA				((unsigned char *)data)
# define S_DATA				len[1]
# define S_NEW				len[0]

typedef struct s_type		t_type;
typedef struct s_bloc		t_bloc;
typedef struct s_posi		t_posi;
typedef struct s_hist		t_hist;

extern t_type				g_mem;

enum						e_fonction
{
	ft_null,
	ft_malloc,
	ft_realloc,
	ft_free,
	ft_dump
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

struct						s_posi
{
	t_bloc					*page;
	t_bloc					*bloc;
};

enum						e_type
{
	tiny = T_SIZE_DATA,
	small = S_SIZE_DATA,
	large = ULONG_MAX
};

struct						s_type
{
	t_bloc					*tiny;
	t_bloc					*small;
	t_bloc					*large;
	t_bloc					*buff[3];
	size_t					hist_last;
	t_hist					histo[H_NB_BLOC];
	enum e_fonction			fonction;

};

void						*malloc(size_t size);
bool						new_page(size_t size, size_t s_page, t_bloc **page,
								enum e_type type);
void						*create_bloc(size_t size, t_bloc *page,
								enum e_type type);
t_posi						find_best(size_t size, t_bloc *page, size_t s_page,
								size_t as_min);
void						place_header(size_t size, t_posi posi,
								enum e_type type, enum e_fonction fonction);

void						free(void *ptr);
bool						delete_bloc(t_posi posi, enum e_type type);
bool						delete_page(t_bloc *page, size_t p_size,
								enum e_type type);
bool						save_buff(t_bloc *page, size_t i, size_t p_size,
								enum e_type type);
t_bloc						*get_buff(size_t s_page, enum e_type type);

void						*realloc(void *ptr, size_t size);
bool						move_bloc(t_posi posi, size_t size,
								enum e_type type[2]);
void						*reset(t_posi posi, size_t s_prev, size_t size,
								enum e_type type);
void						copy_data(void *new, void *data, size_t len[2]);

void						show_alloc_mem();
size_t						p_page(t_bloc *page, char *text, enum e_type type);
size_t						p_bloc(t_bloc *bloc, size_t s_page,
								enum e_type type);
void						p_posi(size_t number, size_t base);

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

t_posi						check_ptr(void *ptr, enum e_fonction fonction);
t_posi						check_list(void *ptr, t_bloc *start,
								enum e_type type);
bool						check_corrupt(t_bloc *ptr, bool page,
								enum e_type type);

void						*check_page(void *ptr, t_bloc *page, size_t p_size,
								enum e_type type);

size_t						finder(size_t size, size_t i);
void						*ft_error(int error);

#endif
