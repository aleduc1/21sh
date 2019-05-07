/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 17:01:09 by aleduc            #+#    #+#             */
/*   Updated: 2019/05/07 21:11:26 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "lexer.h"
#include "parser.h"

int		main(int argc, char **argv, char **environ)
{
  	t_multi	*multi_input;
	char	*input;
	t_lex	*lex;
	t_ast 	*ast;
	t_pos	pos;

	lex = NULL;
	input = NULL;
	multi_input = NULL;
	ast = NULL;
	welcome();
	init_prompt(&pos);
	while (21)
	{
		if (argc && argv && environ)
		{
			input = prompt(multi_input, &pos);
			if(input)
			{
				lex = lexer(input);
				if (lex)
				{
					ft_strdel(&input);
					if ((ast = ast_parser(lex)) && (solo_tree(ast, &pos) < 0))
						interpreter(ast, &pos);
					//run(lex, &pos);
					clean_lex(&lex);
					clean_ast(ast);
				}
			}
		}
	}
	return (0);
}
