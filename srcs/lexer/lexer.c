/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 17:21:29 by aleduc            #+#    #+#             */
/*   Updated: 2019/03/21 19:38:55 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

int		ft_isnumbers(char *str) /* Put this in libft */
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!(ft_isdigit(str[i])))
			return (0);
		i++;
	}
	return (1);
}

t_token	*word_or_number(char *data)
{
	t_token	*token;

	token = NULL;
	if (ft_isnumbers(data))
		token = number(data);
	else
		token = word(data);
	return (token);
}

void	compare_types(t_ptrf **fptr, t_token **token, char *word)
{
	int		i;

	i = 0;
	while ((*fptr)[i].f)
	{
		if (!(ft_strcmp(word, (*fptr)[i].str)))
			*token = (*fptr)[i].f();
		i++;
	}
	if (!(*token))
		*token = word_or_number(word);
	free(*fptr);
}

t_token	*check_type(char *input, int start, int end)
{
	t_ptrf	*fptr;
	char	*word;
	t_token	*token;

	ft_putendl("Je suis dans check_type");
	token = NULL;
	word = ft_strsub(input, start, end - start); // should first contain abc
	ft_putstr("This is the word copied : ");
	ft_putendl(word);
	set_tab_types(&fptr);
	compare_types(&fptr, &token, word);
	ft_memdel((void **)&word);
/* Free tout les pointeurs : token apres l'avoir return pour reading input
	** Et creer le tableau dans une fonction plus haute dans la stack pour pouvoir le free a la fin du lexing
	 */
	return (token);
}

int		skip_whitespace(char *str, int i) /* Put this in libft */
{
	int		cpy;

	cpy = i;
	while (str[cpy] && ft_isspace(str[cpy]))
		cpy++;
	return (cpy);
}

void	reading_input(char *input, t_lex **lex) // Input abc 123
{
	int		i;
	int		j;
	int		to_check;
	t_token	*tok;

	tok = NULL;
	to_check = 0;
	i = 0;
	j = 0;
	while (input[i])
	{
		i = skip_whitespace(input, i);
		j = i;
		while (input[i] && !(ft_isspace(input[i])))
		{
			i++;
			to_check = 1;
		}
		if (to_check)
		{
			tok = check_type(input, j, i);
			ft_putstr("I have a token containing : ");	/*			DEBUGGING			*/
			ft_putendl(tok->data);						/*								*/
//			add_token(lex, tok);
			ft_memdel((void **)&tok);
			ft_putendl("token freed");
			to_check = 0;
		}
	}
}

t_lex	*lexer(char *input)
{
	t_lex	*lex;

	lex = NULL;
	if (ft_strcmp(input, "exit") == 0) //Just in case
		exit(0);
	reading_input(input, &lex);
	return (lex);
}
