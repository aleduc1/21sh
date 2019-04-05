/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 17:01:09 by aleduc            #+#    #+#             */
/*   Updated: 2019/04/05 13:58:16 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "lexer.h"
#include "parser.h"

int		main(int ac, char **av, char **environ)
{
  	t_node	*input;
  	t_pos	pos;
  	char	*inputstr;
	t_lex	*lex;
	t_ast 	*ast;

	lex = NULL;
	inputstr = NULL;
	input = NULL;
	ast = NULL;
	init_prompt(&pos);
	welcome();
	while (21)
	{
		if (ac && av && environ)
		{
			inputstr = prompt(input, &pos); // Don't forget to free inputstr once you are done with it.
			if (inputstr[0])
				lex = lexer(inputstr);
			ft_putendl(inputstr);/* Debugging */
			//dllprinthead(&lex);
			ast = parser(lex);
		}
	}
	return (0);
}
