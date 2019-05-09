/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_stuff.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 20:56:21 by aleduc            #+#    #+#             */
/*   Updated: 2019/05/09 06:40:31 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

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

char	*add_squote_to_str(char **str_addr)
{
	char	*str;
	char	*des;
	int		i;
	int		j;
	int		len;

	str = *str_addr;
	i = 1;
	j = 0;
	len = ft_strlen(str) + 3;
	if (!(des = (char *)ft_memalloc(sizeof(char) * len)))
		return (NULL);
	des[0] = '\'';
	while (str[j])
		des[i++] = str[j++];
	des[i++] = '\'';
	des[i] = '\0';
	return (des);
}

t_token	*handle_string_squote(char *input, int *i, int *last_t, char c)
{
	char	*word;
	char	*word_squote;
	t_token	*tok;

	word = NULL;
	word_squote = NULL;
	tok = NULL;
	(*last_t) = ++(*i);
	while (input[(*i)] != c)
		(*i)++;
	word = ft_strsub(input, *last_t, *i - *last_t);
	word_squote = add_squote_to_str(&word);
	ft_memdel((void **)&word);
	tok = create_token(word_squote, WORD);
	ft_memdel((void **)&word_squote);
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
	while (input[i] && ft_isspace(input[i]))
		i++;
	if (i != cpy)
	{
		tok = create_token(" ", SPACE);
		add_token(lex, &tok);
		clean_inside_token(&tok);
	}
	return (i);
}
