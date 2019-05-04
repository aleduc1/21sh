/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 22:55:39 by aleduc            #+#    #+#             */
/*   Updated: 2019/05/04 22:56:22 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_redir	*redir_struct_heredoc(t_lex **start)
{
	t_redir	*redir_info;
	t_lex	*ptr;

	ptr = *start;
	if (!(redir_info = (t_redir *)ft_memalloc(sizeof(t_redir))))
		return (NULL);
	if (!(redir_info->src_fd = (char **)ft_memalloc(sizeof(char *) * 2)))
		return (NULL);
	redir_info->type = DLESS;
	ft_default(&redir_info);
	ptr = ptr->next;
	if (ptr->token->type == SPACE)
		ptr = ptr->next;
	if (ptr->token->type == WORD)
		redir_info->heredoc = ft_strdup(ptr->token->data);
	return (redir_info);
}

void	handle_heredoc(t_lex **command_node)
{
	t_lex	*start;
	t_lex	*end;
	t_lex	*before_start;
	t_redir	*redir_info;

	start = (*command_node)->token->command;
	end = NULL;
	redir_info = NULL;
	while (start && start->token->type != DLESS)
		start = start->next;
	if (start)
	{
		end_grammar_great(&start, &end, DLESS);
		before_start = detaching(&start, &end);
		redir_info = redir_struct_heredoc(&start);
		ft_putendl("\n The redirect little LL : \n");
		dllprinthead(&start);
		ft_putendl("\n\n");
		clean_lex(&start);
		attach_redir_node(&redir_info, &before_start);
		handle_heredoc(command_node);
	}
	else
		return ;
}
