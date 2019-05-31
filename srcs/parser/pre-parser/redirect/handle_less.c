/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_less.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 19:24:54 by aleduc            #+#    #+#             */
/*   Updated: 2019/05/31 15:55:27 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_redir	*redir_struct_less(t_lex **start)
{
	t_redir	*redir_info;
	t_lex	*ptr;

	ptr = *start;
	if (!(redir_info = (t_redir *)ft_memalloc(sizeof(t_redir))))
		return (NULL);
	if (!(redir_info->src_fd = (char **)ft_memalloc(sizeof(char *) * 2)))
		return (NULL);
	redir_info->type = LESS;
	ft_default(&redir_info);
	ptr = ptr->next;
	if (ptr->token->type == SPACE)
		ptr = ptr->next;
	if (ptr)
		redir_info->filename = ft_strdup(ptr->token->data);
	return (redir_info);
}

int		handle_less(t_lex **command_node)
{
	t_lex	*start;
	t_lex	*end;
	t_lex	*before_start;
	t_lex	*after_end;
	t_redir	*redir_info;

	start = *command_node;
	end = NULL;
	after_end = NULL;
	redir_info = NULL;
	while (start && start->token->type != LESS)
		start = start->next;
	if (start)
	{
		if (end_grammar_great(&start, &end, LESS))
			return (1);
		if (end->next)
			after_end = end->next;
		before_start = detaching(&start, &end);
		redir_info = redir_struct_less(&start);
		clean_lex(&start);
		attach_redir_node(&redir_info, &before_start, &after_end, command_node);
	}
	return (0);
}
