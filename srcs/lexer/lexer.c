/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 17:21:29 by aleduc            #+#    #+#             */
/*   Updated: 2019/05/07 22:16:14 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		handle_tok(t_token **tok, t_lex **lex)
{
	if ((*tok)->data[0])
		add_token(lex, tok);
	ft_strdel(&(*tok)->data);
	ft_memdel((void **)tok);
	return (0);
}

int		init_variables(t_token **tok, int *to_check, int *i, t_tab_type **t)
{
	*tok = NULL;
	*to_check = 0;
	*i = 0;
	set_tab_types(t);
	return (0);
}

int		handle_classic_case(int *i, int *last_t, char **input)
{
	if ((*i) == (*last_t))
	{
		if (dub_possible((*input)[*i]))
			check_double(*input, i);
		(*i)++;
	}
	return (1);
}

void	handle_word_case(int *i, char **input, int *last_t, int *to_check)
{
	(*i)++;
	if ((*input)[(*i)] == '\0')
	{
		if ((*i) != (*last_t))
			(*to_check) = 1;
	}
}

int		handle_string_case(int *i, int *last_t, char **input, t_token **tok)
{
	if ((*i) == (*last_t))
		(*tok) = handle_string((*input), i, last_t);
	return (1);
}

void	reading_input(char *input, t_lex **lex)
{
	int			i;
	int			last_t;
	int			to_check;
	t_token		*tok;
	t_tab_type	*tab_of_type;

	last_t = init_variables(&tok, &to_check, &i, &tab_of_type);
	while (input[i])
	{
		i = handle_whitespace(input, i, lex);
		last_t = i;
		while (input[i] && !(to_check))
		{
			if (ft_isspace(input[i]) && (i != last_t))
				to_check = 1;
			else if (input[i] == '\"')
				to_check = handle_string_case(&i, &last_t, &input, &tok);
			else if (is_in_tab(&tab_of_type, input[i]))
				to_check = handle_classic_case(&i, &last_t, &input);
			else
				handle_word_case(&i, &input, &last_t, &to_check);
		}
		if (to_check)
		{
			if (!tok)
				tok = check_type(&tab_of_type, input, last_t, i);
			to_check = handle_tok(&tok, lex);
		}
	}
	ft_memdel((void **)&tab_of_type);
}

t_lex	*lexer(char *input)
{
	t_lex	*lex;

	lex = NULL;
	reading_input(input, &lex);
	lex = add_delim(&lex);
	simple_command(&lex);
	if (handle_redir(&lex))
	{
		ft_error(0);
		return (NULL);
	}
	remove_space_token(&lex);
	return (lex);
}
