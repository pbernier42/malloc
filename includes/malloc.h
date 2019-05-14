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

# include <stdio.h>

# define T_NB_BLOC			128
# define T_SIZE_PAGE		getpagesize() / 2
# define T_SIZE_BLOC		T_SIZE_PAGE / T_NB_BLOC

# define S_NB_BLOC			128
# define S_SIZE_PAGE		getpagesize() * 4
# define S_SIZE_BLOC		S_SIZE_PAGE / S_NB_BLOC

# define TINY				T_SIZE_BLOC
# define SMALL				S_SIZE_BLOC

# define HEAD				sizeof(t_bloc)

typedef struct s_type	t_type;
typedef struct s_bloc	t_bloc;

struct				s_bloc
{
	size_t			size;
	bool			empty;
	struct	s_bloc	*prev;
	struct	s_bloc	*next;
	void			*data;
};

struct				s_type
{
	t_bloc			*(tiny[T_NB_BLOC]);
	t_bloc			*(small[T_NB_BLOC]);
	t_bloc			*large;
};

//extern t_type			g_mem;

void	*malloc(size_t size);
void	pre_alloc();

void	free(void *ptr);
void	*realloc(void *ptr, size_t size);
void	show_alloc_mem();

#endif
