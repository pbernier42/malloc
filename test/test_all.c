/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbernier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 14:24:24 by pbernier          #+#    #+#             */
/*   Updated: 2019/07/03 14:24:25 by pbernier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <malloc.h>

typedef struct s_test		t_test;
struct s_test	init(int argc, char **argv);

struct			s_test
{
	bool		(*test_malloc)(void);
	bool		(*test_realloc)(void);
	bool		(*test_free)(void);
};

int				main(int argc, char **argv)
{
	struct s_test	test;

	test = init(argc, argv);
}

struct s_test	init(int argc, char **argv)
{
	size_t			i[2];
	char			**str;
	struct s_test	test;

	i[0] = 0;
	str = (char*[3]){"1", "2","3"};
	test = (t_test){NULL, NULL, NULL};

	while (++i[0] < argc)
	{
		i[1] = 0;
		while (argv[i[0]][i[1]] == str[i[0] - 1][i[1]])
			++i[1];
		if (argv[i[0]][i[1]] == "\0" &&
			str[i[0] - 1][i[1]] == "\0");

	}

	(void)argc;
	(void)argv;
	return (test);
}
