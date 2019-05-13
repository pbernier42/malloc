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

# include <stdlib.h>
# include <sys/mman.h>
# include <unistd.h>
# include <stdbool.h>

# include <stdio.h>

# define N	-1
# define M	-1
/*
**# define TINY	16
**# define SMALL	512
**# define LARGE	4000
*/

//extern void *??

typedef struct		s_bloc
{
	//void			*data;
	size_t			size;
	bool			free;
	struct	s_bloc	*prev;
	struct	s_bloc	*next;
	void			*data;
	//void 			data2[TINY];
	//void 			data3[SMALL];
}					t_bloc;

void	*malloc(size_t size);
void	free(void *ptr);
void	*realloc(void *ptr, size_t size);
void	show_alloc_mem();

#endif
