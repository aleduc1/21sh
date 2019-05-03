/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 11:00:04 by aleduc            #+#    #+#             */
/*   Updated: 2019/05/03 18:36:53 by aleduc           ###   ########.fr       */
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

void	defaults(t_redir **struct)
{
	t_redir	*ptr;

	ptr = *struct;
	if (ptr->type == GREAT)
	{
		if (!(ptr->src_fd = (char **)ft_memalloc(sizeof(char *) * 2)))
			return (NULL);
		ptr->src_fd[1] = NULL;
		ptr->src_fd[0] = ft_strdup("1");
	}
}

t_redir	*redir_struct_great(t_lex **start)
{
	t_redir	*struct;
	t_lex	*ptr;

	ptr = *start;
	if (!(struct = (t_redir *)ft_memalloc(sizeof(t_redir))))
		return (NULL);
	struct->type = GREAT;
	if (ptr->token->type == NUMBER)
		struct->src_fd[1] = ptr->token->type;
	else
		defaults(&struct);
	while (ptr->token->type != GREAT)
		ptr = ptr->next;
	ptr = ptr->next;
	if (ptr->token->type == SPACE)
		ptr = ptr->next;
	else
		struct->filename == ft_strdup(ptr->token->data);
	return (struct);
}

void	handle_great(t_lex **command_node)
{
	t_lex	*start;
	t_lex	*end;
	t_redir	*struct;

	start = (*command_node)->token->command;
	end = NULL;
	struct = NULL;
	while (start && start->token->type != GREAT)
		start = start->next;
	if (start)
	{
		start_grammar_great(&start);
		end_grammar_great(&start, &end);
		detaching(&start, &end);
		struct = redir_struct_great(&start);
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
			handle_great(&ptr);
			//		handle_upper_and(&ptr);
			//		handle_and_upper(&ptr);
		}
		ptr = ptr->next;
	}
}
