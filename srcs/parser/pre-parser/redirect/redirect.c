/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 11:00:04 by aleduc            #+#    #+#             */
/*   Updated: 2019/05/03 12:38:32 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"


int		great_exist(t_lex **command)
{
	t_lex	*ptr;

	ptr = *command;
	while (ptr)
	{
		if (ptr->token->type == GREAT)
			return (1);
		ptr = ptr->next;
	}
	return (0);
}

t_redir	*handle_upper(t_lex **command_node)
{
	t_lex	*start;
	t_lex	*end;
	t_redir	*struct;

	start = (*command_node)->token->command;
	end = NULL;
	struct = NULL;
	if (great_exist(command_node))
	{
		while (start->token->type != GREAT)
			start = start->next;
		start = start_grammar_great(&start);
		end = end_grammar_great(&start);
		detach(&start, &end);
		struct = redir_struct(&start);
		clean_redir(&start);
	}
	return (struct);
}

void	redirect(t_lex **lex)
{
	t_lex	*ptr;

	ptr = *lex;
	while (ptr)
	{
		if (ptr->token->type == CMD)
		{
			handle_upper(&ptr);
			handle_upper_and(&ptr);
			handle_and_upper(&ptr);
		}
		ptr = ptr->next;
	}
}
