/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbernier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 14:39:39 by pbernier          #+#    #+#             */
/*   Updated: 2019/05/06 14:39:39 by pbernier         ###   ########.fr       */
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

# define SIZE_HEAD			((int)sizeof(t_bloc))

# define T_SIZE_DATA		16
# define T_SIZE_PAGE		(getpagesize() * 2)
# define T_SIZE_BLOC		(SIZE_HEAD + T_SIZE_DATA)
# define T_SIZE_ZERO		(T_SIZE_PAGE % T_SIZE_BLOC)
# define T_NB_BLOC			(T_SIZE_PAGE / (float)T_SIZE_BLOC)

# define S_SIZE_DATA		123
# define S_SIZE_PAGE		(getpagesize() * 4)
# define S_SIZE_BLOC		(SIZE_HEAD + S_SIZE_DATA)
# define S_SIZE_ZERO		(S_SIZE_PAGE % S_SIZE_BLOC)
# define S_NB_BLOC			(S_SIZE_PAGE / (float)S_SIZE_BLOC)

# define TINY				T_SIZE_DATA
# define SMALL				S_SIZE_DATA
# define LARGE 				UINT_MAX
//4 294 967 295

typedef struct s_type	t_type;
typedef struct s_bloc	t_bloc;

struct				s_bloc
{
	size_t			size;
	bool			empty;
	struct	s_bloc	*prev;
	struct	s_bloc	*next;
};

struct				s_type
{
	t_bloc			*tiny;
	t_bloc			*small;
	t_bloc			*large;
};

//extern t_type			g_mem;

void	*malloc(size_t size);
void	pre_alloc(size_t mem);

void	free(void *ptr);
void	*realloc(void *ptr, size_t size);
void	show_alloc_mem();

#endif
