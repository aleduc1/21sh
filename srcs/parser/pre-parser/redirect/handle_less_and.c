/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_less_and.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 20:07:09 by aleduc            #+#    #+#             */
/*   Updated: 2019/05/04 20:09:12 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_redir	*redir_struct_less_and(t_lex **start)
{
	t_redir	*redir_info;
	t_lex	*ptr;

	ptr = *start;
	if (!(redir_info = (t_redir *)ft_memalloc(sizeof(t_redir))))
		return (NULL);
	if (!(redir_info->src_fd = (char **)ft_memalloc(sizeof(char *) * 3)))
		return (NULL);
	redir_info->type = LESSAMP;
	if (ptr->token->type == NUMBER)
		redir_info->src_fd[0] = ft_strdup(ptr->token->data);
	else
		ft_default(&redir_info);
	while (ptr->token->type != LESSAMP)
		ptr = ptr->next;
	ptr = ptr->next;
	if (ptr->token->type == SPACE)
		ptr = ptr->next;
	if (ptr)
	{
		if (ptr->token->type == NUMBER)
			redir_info->dest_fd = ft_strdup(ptr->token->data);
		else
			redir_info->filename = ft_strdup(ptr->token->data);
	}
	return (redir_info);
}

void	handle_less_and(t_lex **command_node)
{
	t_lex	*start;
	t_lex	*end;
	t_lex	*before_start;
	t_redir	*redir_info;

	start = (*command_node)->token->command;
	end = NULL;
	redir_info = NULL;
	while (start && start->token->type != LESSAMP)
		start = start->next;
	if (start)
	{
		start_grammar_great(&start);
		end_grammar_great(&start, &end, LESSAMP);
		before_start = detaching(&start, &end);
		redir_info = redir_struct_less_and(&start);
		ft_putendl("\n The redirect little LL : \n");
		dllprinthead(&start);
		ft_putendl("\n\n");
		clean_lex(&start);
		attach_redir_node(&redir_info, &before_start);
		handle_less_and(command_node);
	}
	else
		return ;
}