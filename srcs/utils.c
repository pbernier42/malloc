/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlecart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 19:57:04 by rlecart           #+#    #+#             */
/*   Updated: 2019/05/17 23:16:13 by rlecart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

size_t		finder(size_t size, bool i)
{
	if (size > 0 && size <= TINY)
		return (i == PAGE ? T_SIZE_PAGE : TINY);
	else if (size > TINY && size <= SMALL)
		return (i == PAGE ? S_SIZE_PAGE : SMALL);
	else if (size <= LARGE)
		return (size);
	return (0);
}
