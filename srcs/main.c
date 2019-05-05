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
  	t_multi	*input;
	t_pos	pos;
	char	*inputstr;
	t_lex	*lex;
	t_ast 	*ast;

	lex = NULL;
	inputstr = NULL;
	input = NULL;
	ast = NULL;
	welcome();
	init_prompt(&pos);
	while (21)
	{
		if (argc && argv && environ)
		{
			// inputstr = heredoc("test", &pos);
			// ft_putendl(inputstr);
			// free(inputstr);
			inputstr = prompt(input, &pos); // Don't forget to free inputstr once you are done with it.
			lex = lexer(inputstr);
			if (lex)
			{
//				ft_strdel(&inputstr);
				ft_putendl("\n\nThe lexer after the whole lexing phase : \n\n");
				dllprinthead(&lex);
//				ast = ast_parser(lex);
//				clean_lex(&lex);
			}
//			else
//				clean_lex(&lex);
		}
	}
	return (0);
}
