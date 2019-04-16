/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 17:01:09 by aleduc            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/04/15 16:10:39 by mbellaic         ###   ########.fr       */
=======
/*   Updated: 2019/04/16 16:26:11 by aleduc           ###   ########.fr       */
>>>>>>> f15163615368dc0b64e5f7153a472528a9362fbe
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
			if (inputstr)
				lex = lexer(inputstr);
<<<<<<< HEAD
			ast = ast_parser(lex);
=======
			dllprinthead(&lex);
//			ast = parser(lex);
			clean_lex(&lex);
>>>>>>> f15163615368dc0b64e5f7153a472528a9362fbe
		}
	}
	return (0);
}
