/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 17:01:09 by aleduc            #+#    #+#             */
/*   Updated: 2019/05/05 17:10:17 by aleduc           ###   ########.fr       */
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
					// ft_strdel(&inputstr);
					ft_putendl("=====TOKEN_STREAM=====");
					dllprinthead(&lex);
					ft_putendl("======================");
					//ast = ast_parser(lex);
					// clean_lex(&lex);
				}
				cmd_parser(lex);
				// else
					// clean_lex(&lex);
			}
		}
	}
	return (0);
}
