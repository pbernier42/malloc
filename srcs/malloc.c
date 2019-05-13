/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbernier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 14:43:20 by pbernier          #+#    #+#             */
/*   Updated: 2019/05/06 14:43:21 by pbernier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

void		*base_bloc;

// t_bloc		*test(t_bloc *test)
// {
// 	return (test)
// }

void		*malloc(size_t size)
{
	t_bloc	bloc;

	bloc = base_bloc;
	mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	printf("..[%lu]\n", sizeof(t_bloc));
	printf("..[%s]\n", (char*)bloc);
	(void)size;
	return (NULL);
}

g_bonjour
{
	s_ *small
	tiny[]
	large[]
}


SMALL
| | | | | |   | | | | | | | | |

TINY
| | | | | | | | | | | | | | |

LARGE
| | | | | | | | | | | | | | |
