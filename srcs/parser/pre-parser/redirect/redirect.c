/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 11:00:04 by aleduc            #+#    #+#             */
/*   Updated: 2019/05/03 16:06:40 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	start_grammar_great(t_lex **start)
{
	if ((*start)->prev->token->type == NUMBER)
		(*start) = (*start)->prev;
}

void	end_grammar_great(t_lex **start, t_lex **end)
{
	(*end) = (*start);
	(*end) = (*end)->next;
	if ((*end)->token->type == GREAT)
		(*end) = (*end)->next;
	if (((*end)->token->type == SPACE) && ((*end)->next))
		(*end) = (*end)->next;
}

void	detaching(t_lex **start, t_lex **end)
{
	t_lex	*before_start;
	t_lex	*after_end;

	before_start = (*start)->prev;
	after_end = (*end)->next;
	before_start->next = after_end;
	if (after_end)
		after_end->prev = before_start;
	(*start)->prev = NULL;
	(*end)->next = NULL;
}

void	handle_upper(t_lex **command_node)
{
	t_lex	*start;
	t_lex	*end;
	//	t_redir	*struct;

	start = (*command_node)->token->command;
	end = NULL;
	//	struct = NULL;
	while (start && start->token->type != GREAT)
		start = start->next;
	if (start)
	{
		start_grammar_great(&start);
		end_grammar_great(&start, &end);
		detaching(&start, &end);
		//			struct = redir_struct(&start);
		//			clean_redir(&start);
		//			attach_redir_node();
	}
}

void	handle_redir(t_lex **lex)
{
	t_lex	*ptr;

	ptr = *lex;
	while (ptr)
	{
		if (ptr->token->type == CMD)
		{
			handle_upper(&ptr);
			//			handle_upper_and(&ptr);
			//			handle_and_upper(&ptr);
		}
		ptr = ptr->next;
	}
}
