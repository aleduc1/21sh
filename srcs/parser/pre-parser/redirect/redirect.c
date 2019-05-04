/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 11:00:04 by aleduc            #+#    #+#             */
/*   Updated: 2019/05/03 22:11:59 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdio.h>

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

void	ft_default(t_redir **redirr)
{
	t_redir	*ptr;

	ptr = *redirr;
	if (ptr->type == GREAT)
	{
		ptr->src_fd[1] = NULL;
		ptr->src_fd[0] = ft_strdup("1");
	}
}

t_redir	*redir_struct_great(t_lex **start)
{
	t_redir	*redirr;
	t_lex	*ptr;

	ptr = *start;
	if (!(redirr = (t_redir *)ft_memalloc(sizeof(t_redir))))
		return (NULL);
	if (!(redirr->src_fd = (char **)ft_memalloc(sizeof(char *) * 2)))
		return (NULL);
	redirr->type = GREAT;
	if (ptr->token->type == NUMBER)
	{
		redirr->src_fd[0] = ft_strdup(ptr->token->data);
		redirr->src_fd[1] = NULL;
	}
	else
		ft_default(&redirr);
	while (ptr->token->type != GREAT)
		ptr = ptr->next;
	ptr = ptr->next;
	if (ptr->token->type == SPACE)
		ptr = ptr->next;
	redirr->filename = ft_strdup(ptr->token->data);
	return (redirr);
}

/*
 ** Testing fct
 */

/*void	print_struct(t_redir **redirr)
 **{
 **	t_redir	*ptr;
 **
 **	ptr = *redirr;
 **	printf("src_fd : %s\ndest_fd : %s\n type : %d\nfilename : %s\nHeredoc : %s\nclose : %d\n", ptr->src_fd[0], ptr->dest_fd, ptr->type, ptr->filename, ptr->heredoc, ptr->close);
 }*/

void	handle_great(t_lex **command_node)
{
	t_lex	*start;
	t_lex	*end;
	t_redir	*redirr;

	start = (*command_node)->token->command;
	end = NULL;
	redirr = NULL;
	while (start && start->token->type != GREAT)
		start = start->next;
	if (start)
	{
		start_grammar_great(&start);
		end_grammar_great(&start, &end);
		detaching(&start, &end);
		redirr = redir_struct_great(&start);
		clean_lex(&start);
		attach_redir_node(); //pause
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
