/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 17:01:09 by aleduc            #+#    #+#             */
/*   Updated: 2019/05/08 03:21:25 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "lexer.h"
#include "parser.h"

int			siginthandler(int signum)
{
	(void)signum;
	ft_printf("oui\n");
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
	init_prompt(&pos);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	while (21)
	{
		if (argc && argv && environ)
			if ((input = prompt(multi_input, &pos)))
				run(input, &pos);
	}
	return (0);
}
