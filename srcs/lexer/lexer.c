/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 17:21:29 by aleduc            #+#    #+#             */
/*   Updated: 2019/05/02 18:41:16 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

t_lex	*add_delim(t_lex **lex)
{
	t_lex	*head;
	t_lex	*tail;
	t_lex	*node;
	t_lex	*nd_node;
	t_token	*token;

	token = create_token("delim", DELIM);
	node = new_node(&token);
	nd_node = new_node(&token);
	head = *lex;
	tail = *lex;
	while (tail && tail->next)
		tail = tail->next;
	dllinsfront(&head, &nd_node);
	dllinsback(&tail, &node);
	return (head);
}

void	add_token(t_lex **lexer, t_token **token)
{
	t_lex	*tail;
	t_lex	*node;

	node = new_node(token);
	tail = *lexer;
	if (!(*lexer))
		*lexer = node;
	else
	{
		while (tail->next)
			tail = tail->next;
		dllinsback(&tail, &node);
	}
}

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
		token = create_token(data, NUMBER);
	else
		token = create_token(data, WORD);
	return (token);
}

void	compare_types(t_tab_type **tab_of_type, t_token **token, char *word)
{
	int		i;

	i = 0;
	while ((*tab_of_type)[i].type != NUL)
	{
		if (!(ft_strcmp(word, (*tab_of_type)[i].str)))
			*token = create_token((*tab_of_type)[i].str, (*tab_of_type)[i].type);
		i++;
	}
	if (!(*token))
		*token = word_or_number(word);
}

int		is_in_tab(t_tab_type **tab_of_type, char c)
{
	int		i;

	i = 0;
	while ((*tab_of_type)[i].type != NUL)
	{
		if ((*tab_of_type)[i].str[0] == c)
			return (1);
		i++;
	}
	return (0);
}

t_token	*check_type(t_tab_type **tab_of_type, char *input, int start, int end)
{
	char	*word;
	t_token	*token;

	token = NULL;
	word = ft_strsub(input, start, end - start);
	compare_types(tab_of_type, &token, word);
	ft_memdel((void **)&word);
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

int		dub_possible(char c)
{
	if (c == '|' || c == '&' || c == '>' || c == '<' || c == ';')
		return (1);
	return (0);
}

t_token	*handle_string(char *input, int *i, int *last_t)
{
	char	*word;
	t_token	*tok;

	word = NULL;
	tok = NULL;
	(*last_t) = ++(*i);
	while (input[(*i)] != '\"')
		(*i)++;
	word = ft_strsub(input, *last_t, *i - *last_t);
	tok = create_token(word, WORD);
	ft_memdel((void **)&word);
	(*i)++;
	return (tok);
}

int		is_amper(char c)
{
	if (c == '&')
		return (1);
	return (0);
}

int		is_lesser_greater(char c)
{
	if (c == '>' || c == '<')
		return (1);
	return (0);
}

int		is_hyph(char c)
{
	if (c == '-')
		return (1);
	return (0);
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
			{
				if ((input[(*i) + 2]) && (is_hyph(input[(*i) + 2])))
					(*i)++;
				(*i)++;
			}
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


int		handle_whitespace(char *input, int i)
{
	int		cpy;

	cpy = i;
	i = skip_whitespace(input, i);
	if (i != cpy)
	{
		create_space_token();
		
	}
	return (i);
}

void	reading_input(char *input, t_lex **lex)
{
	int			i;
	int			last_t;
	int			to_check;
	t_token		*tok;
	t_tab_type	*tab_of_type;

	tok = NULL;
	to_check = 0;
	i = 0;
	last_t = 0;
	set_tab_types(&tab_of_type);
	while (input[i])
	{
		i = skip_whitespace(input, i); // Skip the found whitespaces till we meet a word
		//i = handle_whitespace() -> skip_whitespace with state of i, if i != create whitespace token
		last_t = i;                    // save starting point in last_t
		while (input[i] && !(to_check)) // If to_check == 1 we need to create a token
		{
			if (ft_isspace(input[i]) && (i != last_t)) // If we reached EOW send it to create a token
					to_check = 1;
			else if (input[i] == '\"') // Create a string token of whats inside ""
			{
				if (i == last_t)
					tok = handle_string(input, &i, &last_t);
				to_check = 1;
			}
			else if (is_in_tab(&tab_of_type, input[i])) // If input[i] is | or ;
			{
				if (i == last_t)
				{
					if (dub_possible(input[i]))	// Checking if double char token needed
						check_double(input, &i);
					i++;
				}
				to_check = 1;
			}
			else  // if current char was part of a word, keep going till you reach space or \0
			{
				i++;
				if (input[i] == '\0')
				{
					if (i != last_t)
						to_check = 1;
				}
			}
		}
		if (to_check)  // we enter this when we know we can create a token safely
		{
			if (!tok) // If the token doesnt already exist (via handle_string), create it
				tok = check_type(&tab_of_type, input, last_t, i);
			if (tok->data[0])		// When the token is created or was created in string fct, add it to the lex
				add_token(lex, &tok);
			ft_memdel((void **)&tok);
			to_check = 0;
		}
	}
}

t_lex	*lexer(char *input)
{
	t_lex	*lex;

	lex = NULL;
	if (ft_strcmp(input, "exit") == 0)
		exit(0);
	reading_input(input, &lex);
	lex = add_delim(&lex);
//	handle_redir(&lex);
//	simple_command(&lex);
	return (lex);
}
