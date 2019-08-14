/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbernier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 14:53:47 by pbernier          #+#    #+#             */
/*   Updated: 2019/08/12 14:53:48 by pbernier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "includes/malloc.h"
#include <limits.h>

int main()
{
	show_dump_mem(malloc(10));
	show_dump_mem(malloc(10));
	show_alloc_mem();
}
