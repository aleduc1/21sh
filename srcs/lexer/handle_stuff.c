/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_stuff.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 20:56:21 by aleduc            #+#    #+#             */
/*   Updated: 2019/05/07 23:42:07 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		skip_whitespace(char *str, int i)
{
	int		cpy;

	cpy = i;
	while (str[cpy] && ft_isspace(str[cpy]))
		cpy++;
	return (cpy);
}

int		dub_possible(char c)
{
	if (c == '|' || c == '&' || c == '>' || c == '<' || c == ';')
		return (1);
	return (0);
}

t_token	*handle_string(char *input, int *i, int *last_t, char c)
{
	char	*word;
	t_token	*tok;

	word = NULL;
	tok = NULL;
	(*last_t) = ++(*i);
	while (input[(*i)] != c)
		(*i)++;
	word = ft_strsub(input, *last_t, *i - *last_t);
	tok = create_token(word, WORD);
	ft_memdel((void **)&word);
	(*i)++;
	return (tok);
}

void	check_double(char *input, int *i)
{
	if (input[(*i) + 1])
	{
		if (input[(*i)] == input[(*i) + 1])
			(*i)++;
		else if (is_amper(input[(*i)]))
		{
			if (is_lesser_greater(input[(*i) + 1]))
				(*i)++;
		}
		else if (is_lesser_greater(input[(*i)]))
		{
			if (is_amper(input[(*i) + 1]))
			{
				if ((input[(*i) + 2]) && (is_hyph(input[(*i) + 2])))
					(*i)++;
				(*i)++;
			}
		}
	}
}

int		handle_whitespace(char *input, int i, t_lex **lex)
{
	int		cpy;
	t_token	*tok;

	tok = NULL;
	cpy = i;
	i = skip_whitespace(input, i);
	if (i != cpy)
	{
		tok = create_token(" ", SPACE);
		add_token(lex, &tok);
		clean_inside_token(&tok);
	}
	return (i);
}
