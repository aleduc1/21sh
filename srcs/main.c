/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 17:01:09 by aleduc            #+#    #+#             */
/*   Updated: 2019/03/12 18:43:46 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "lexer.h"

int		main(int ac, char **av, char **environ)
{
  t_node	*input;
  t_pos	pos;
  char	*inputstr;
	t_lex	*lex;

	lex = NULL;
	inputstr = NULL;
  input = NULL;
  init_prompt(&pos);
  welcome();
  while (21)
  {
		if (ac && av && environ)
		{
			inputstr = prompt(input, &pos);
			ft_putendl(inputstr);/* Debugging */
			if (inputstr[0])
			lex = lexer(inputstr);
			ft_putendl(inputstr);/* Debugging */
		}
  }
	return (0);
}
