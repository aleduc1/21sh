/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 17:01:09 by aleduc            #+#    #+#             */
/*   Updated: 2019/05/08 14:23:29 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "lexer.h"
#include "parser.h"
#include "env.h"

int			siginthandler(int signum)
{
	(void)signum;
	ft_printf("oui\n");
}

void		flags(int argc, char **argv)
{
	g_print_ast = 0;
	if (argc >= 2)
	{
		if (strcmp(argv[1], "--ast") == 0)
			g_print_ast = 1;
		if (strcmp(argv[1], "-a") == 0)
			g_print_ast = 1;
	}
	return ;
}

void		run(char *input, t_pos *pos)
{
	t_lex	*lex;
	t_ast	*ast;

	lex = NULL;
	ast = NULL;
	if ((lex = lexer(input)))
	{
		ft_strdel(&input);
		if ((ast = ast_parser(lex)) && (solo_tree(ast, pos) < 0))
			interpreter(ast, pos);
		clean_lex(&lex);
		clean_ast(ast);
	}
}

int			main(int argc, char **argv, char **environ)
{
	t_multi	*multi_input;
	char	*input;
	t_pos	pos;

	input = NULL;
	multi_input = NULL;
	welcome();
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	flags(argc, argv);
	init_prompt(&pos);
	while (21)
	{
		if (argc && argv && environ)
			if ((input = prompt(multi_input, &pos)))
			{
				check_is_env_command(&input);
				if (input)
					run(input, &pos);
				check_delete_env_command();
			}
	}
	return (0);
}
