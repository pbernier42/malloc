/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbernier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 14:43:38 by pbernier          #+#    #+#             */
/*   Updated: 2019/05/06 14:43:39 by pbernier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** #include <malloc.h>
**t_type		g_mem;
**t_visu		visu_total;
**
**
**typedef struct s_visu		t_visu;
**void	show_visual_mem(void *ptr);
**void	visu_page(t_bloc *page, void *ptr);
**t_visu	visu_bloc(t_bloc *bloc, t_visu visu_page, void *ptr);
**void	visu_wink(size_t cursor, size_t end, size_t ptr);
**size_t	points_len(size_t len);
**void	visu_points(size_t len, size_t real, char *color);
**
**
**# define V_POINT		16
**# define V_LAST			true
**# define V_PAGE			visu_page
**# define V_TOTAL		visu_total
**
**struct			s_visu
**{
**	enum e_type	type;
**	size_t		name;
**	size_t		head;
**	size_t		data;
**	size_t		zero;
**	size_t		free;
**	size_t		size;
**};
**
**
**void	show_visual_mem(void *ptr)
**{
**	visu_page(G_TINY, ptr);
**	visu_page(G_SMALL, ptr);
**	visu_page(G_LARGE, ptr);
**	//visu_page(G_BUFF[0], ptr);
**	//visu_page(G_BUFF[1], ptr);
**	//visu_page(G_BUFF[2], ptr);
**}
**
**void	visu_page(t_bloc *page, void *ptr)
**{
**	static unsigned short	list = 0;
**	enum e_type				type;
**	t_visu					visu_page;
**	bool					buff;
**
**	if (!page)
**		return ;
**	buff = (page == G_BUFF[0] || page == G_BUFF[1]
**		|| page == G_BUFF[2]) ? true : false;
**	type = ((enum e_type[3]){tiny, small, large})[list % 3];
**	V_PAGE = ((t_visu){type, 0, 0, 0, 0, 0, type
**		!= large ? S_PAGE(type) : 0});
**	if (V_PAGE.type == large && !buff && page->next != page)
**		page = page->next;
**	while (page)
**	{
**		if (list >= 3)
**			write(1, "BUFF ", 5);
**		write(1, ((char*[3]){"TINY = [","SMALL = [","LARGE = ["})[list % 3],
**			((size_t[3]){8, 9, 9})[list % 3]);
**		p_posi((size_t)page, 16);
**		write(1, "]\n", 2);
**		if (V_PAGE.type == large)
**			V_PAGE.size = S_PAGE(page->size);
**		V_PAGE = visu_bloc(page, V_PAGE, ptr);
**		page = (page == G_LARGE || buff) ? NULL : page->next;
**	}
**	if (++list >= 6)
**		list = 0;
**	else
**		write(1, "\n", 1);
**	return ;
**}
**
**t_visu	visu_bloc(t_bloc *bloc, t_visu visu_page, void *ptr)
**{
**	void			*cursor;
**	size_t			page_end;
**	size_t			align;
**	size_t			zero;
**
**	++V_PAGE.name;
**	cursor = bloc;
**	page_end = (size_t)cursor + V_PAGE.size;
**	while ((size_t)cursor < page_end)
**	{
**		++V_PAGE.head;
**		visu_wink((size_t)cursor, (size_t)cursor + SIZE_HEAD, (size_t)ptr);
**		visu_points(SIZE_HEAD, points_len(SIZE_HEAD), BLUE);
**		V_PAGE.data += CURSOR->size;
**		visu_wink((size_t)cursor + SIZE_HEAD,
**			(size_t)cursor + SIZE_HEAD + CURSOR->size, (size_t)ptr);
**		visu_points(CURSOR->size, points_len(CURSOR->size),
**			!CURSOR->empty ? GREEN : GREY);
**		zero = A_ZERO(CURSOR->size, ((V_PAGE.type != large) ? A_NB : GPS));
**		align = CURSOR->size + SIZE_HEAD + zero;
**		visu_wink((size_t)cursor + CURSOR->size + SIZE_HEAD,
**			(size_t)cursor + align, (size_t)ptr);
**		visu_points(zero, points_len(zero), GREY);
**		V_PAGE.zero += zero;
**		cursor += align;
**	}
**	write(1, "\n", 1);
**	return (visu_page);
**}
**
**void	visu_wink(size_t cursor, size_t end, size_t ptr)
**{
**	if (!ptr)
**		return ;
**	if (cursor <= (size_t)ptr && end > (size_t)ptr)
**		write(1, WINK, 4);
**}
**
**size_t	points_len(size_t len)
**{
**	size_t adjust;
**
**	adjust = len / V_POINT;
**	if ((adjust == 0 && len > 0)|| adjust > 6)
**		return (1);
**	return (adjust);
**}
**
**void	visu_points(size_t len, size_t real, char *color)
**{
**	size_t	i;
**	char	points[real + 1];
**
**	i = 0;
**	while (i <= real)
**		points[i++] = '.';
**	write(1, color, 10);
**	if (real == 1 && (len / V_POINT) > 6)
**	{
**		write (1, points, real);
**		p_posi(len, 10);
**	}
**	write (1, points, real);
**	write (1, RESET, 4);
**	return ;
**}
*/
