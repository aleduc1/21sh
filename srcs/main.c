/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 17:01:09 by aleduc            #+#    #+#             */
/*   Updated: 2019/05/04 02:24:30 by sbelondr         ###   ########.fr       */
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
			inputstr = prompt(input, &pos); // Don't forget to free inputstr once you are done with it.
			lex = lexer(inputstr);
//			ft_strdel(&inputstr);
//			dllprinthead(&lex);
//			ast = ast_parser(lex);
			clean_lex(&lex);
		}
	}
	return (0);
}
