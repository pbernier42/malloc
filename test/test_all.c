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

t_test			init(size_t argc, char **argv);
bool			test_malloc();

struct			s_test
{
	bool		(*test_malloc)(void);
	bool		(*test_realloc)(void);
	bool		(*test_free)(void);
};



int				main(int argc, char **argv)
{
	t_test		test;

	test = init(argc, argv);
	return (1);
}

t_test			init(size_t argc, char **argv)
{
	size_t		i[2];
	char		**str;
	t_test		test;
	bool		init;

	i[0] = 0;
	str = (char*[3]){"malloc", "realloc","free"};
	init = false;
	while (++i[0] < argc)
	{
		printf("[%s]\n", argv[i[0]]);
		i[1] = 0;
		while (argv[i[0]][i[1]] &&
			(argv[i[0]][i[1]] == str[i[0] - 1][i[1]] ||
			argv[i[0]][i[1]] == (str[i[0] - 1][i[1]] + 32)))
			++i[1];
		if (argv[i[0]][i[1]] == '\0' &&
			str[i[0] - 1][i[1]] == '\0')
		{
			if (!init)
				init = true;
			if (i[0] - 1 == )
			printf("b");
		}
	}

	//printf("{%p}\n", test.test_malloc);
	(void)argc;
	(void)argv;
	return ((t_test){NULL, NULL, NULL});
}

bool			test_malloc()
{
	return(1);
}
