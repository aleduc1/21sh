/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 17:01:09 by aleduc            #+#    #+#             */
/*   Updated: 2019/07/09 13:17:07 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "lexer.h"
#include "parser.h"
#include "env.h"
#include "builtins.h"

int		siginthandler(int signum)
{
	(void)signum;
	ft_printf("signal handler\n");
	return (0);
}

void	flags(int argc, char **argv)
{
	g_print_ast = 0;
	if (argc >= 2)
	{
		if (ft_strcmp(argv[1], "--ast") == 0)
			g_print_ast = 1;
		if (ft_strcmp(argv[1], "-a") == 0)
			g_print_ast = 1;
	}
	return ;
}

int		check_whitespace_input(char *input)
{
	int		i;

	i = 0;
	while (input[i])
	{
		if (ft_isspace(input[i]))
			i++;
		else
			return (1);
	}
	return (0);
}

void	run(char *input, t_pos *pos)
{
	t_lex	*lex;
	t_ast	*ast;

	lex = NULL;
	ast = NULL;
	if ((check_whitespace_input(input)) && (lex = lexer(input)))
	{
		ft_strdel(&input);
		if ((ast = ast_parser(lex)) && (solo_tree(ast, pos) < 0))
			interpreter(ast, pos);
		clean_lex(&lex);
		clean_ast(ast);
	}
	else if (input)
	{
		ft_strdel(&input);
		clean_lex(&lex);
		clean_ast(ast);
	}
	dllprinthead(&lex);
}

/*
**void	script_exec(char **argv, t_pos pos)
**{
**	int		i;
**	char	*src;
**
**	i = -1;
**	while (argv[++i])
**	{
**		src = ft_strdup(argv[i]);
**		run(src, &pos);
**	}
**	exit(0);
**}
*/

int		main(int argc, char **argv, char **environ)
{
	t_multi	*multi_input;
	char	*input;
	t_pos	pos;

	input = NULL;
	multi_input = NULL;
	if (isatty(STDIN_FILENO) == 0)
		return (1);
	welcome();
	sig_ign();
	flags(argc, argv);
	init_prompt(&pos);
	while (21)
	{
		if (argc && argv && environ)
		{
			if ((input = prompt(multi_input, &pos)))
				run(input, &pos);
		}
	}
	return (0);
}
