/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 11:00:04 by aleduc            #+#    #+#             */
/*   Updated: 2019/05/04 14:27:27 by aleduc           ###   ########.fr       */
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

t_lex	*detaching(t_lex **start, t_lex **end)
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
	return (before_start);
}

void	ft_default(t_redir **redir_info)
{
	t_redir	*ptr;

	ptr = *redir_info;
	if (ptr->type == GREAT)
	{
		ptr->src_fd[1] = NULL;
		ptr->src_fd[0] = ft_strdup("1");
	}
}

t_redir	*redir_struct_great(t_lex **start)
{
	t_redir	*redir_info;
	t_lex	*ptr;

	ptr = *start;
	if (!(redir_info = (t_redir *)ft_memalloc(sizeof(t_redir))))
		return (NULL);
	if (!(redir_info->src_fd = (char **)ft_memalloc(sizeof(char *) * 2)))
		return (NULL);
	redir_info->type = GREAT;
	if (ptr->token->type == NUMBER)
	{
		redir_info->src_fd[0] = ft_strdup(ptr->token->data);
		redir_info->src_fd[1] = NULL;
	}
	else
		ft_default(&redir_info);
	while (ptr->token->type != GREAT)
		ptr = ptr->next;
	ptr = ptr->next;
	if (ptr->token->type == SPACE)
		ptr = ptr->next;
	redir_info->filename = ft_strdup(ptr->token->data);
	return (redir_info);
}

/*
** Testing fct
*/

void	print_struct(t_redir **redir_info)
{
 	t_redir	*ptr;
 
 	ptr = *redir_info;
 	printf("src_fd : %s\ndest_fd : %s\n type : %d\nfilename : %s\nHeredoc : %s\nclose : %d\n", ptr->src_fd[0], ptr->dest_fd, ptr->type, ptr->filename, ptr->heredoc, ptr->close);
}

void	attach_redir_node(t_redir **redir_info, t_lex **before_start)
{
	t_token	*tok;
	t_lex	*redir_node;

	tok = create_token("redir", REDIR);
	redir_node = new_redir_node(&tok, redir_info);
	ft_putendl("Whats inside the redir node : ");		/* ************ */
	ft_putstr("token == ");								/*				*/
	ft_putendl(redir_node->token->data);				/*	Debugging	*/
	ft_putendl("\nWhats inside the redir struct : \n");	/*				*/
	print_struct(&redir_node->redir);					/* ************ */
	dllinsafter(before_start, &redir_node);
}

void	handle_great(t_lex **command_node)
{
	t_lex	*start;
	t_lex	*end;
	t_lex	*before_start;
	t_redir	*redir_info;

	start = (*command_node)->token->command;
	end = NULL;
	redir_info = NULL;
	while (start && start->token->type != GREAT)
		start = start->next;
	if (start)
	{
		start_grammar_great(&start);
		end_grammar_great(&start, &end);
		before_start = detaching(&start, &end);
		redir_info = redir_struct_great(&start);
		ft_putendl("\n The redirect little LL : \n");
		dllprinthead(&start);
		ft_putendl("\n\n");
		clean_lex(&start);
		attach_redir_node(&redir_info, &before_start);
		handle_great(command_node);
	}
	else
		return ;
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
