/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attach.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 16:04:00 by aleduc            #+#    #+#             */
/*   Updated: 2019/06/02 17:34:23 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	detach(t_lex **start, t_lex **end)
{
	t_lex *beforestart;
	t_lex *beforeend;

	beforestart = (*start)->prev;
	beforeend = (*end)->prev;
	beforestart->next = NULL;
	beforeend->next = NULL;
	(*start)->prev = NULL;
	(*end)->prev = NULL;
}

void	attach(t_lex **head, t_lex **node, t_lex **end)
{
	t_lex	*ptr;

	ptr = dlllastnode(head);
	ptr->next = *node;
	(*end)->prev = *node;
	(*node)->prev = ptr;
	(*node)->next = *end;
}

t_lex	*detaching(t_lex **start, t_lex **end)
{
	t_lex	*before_start;
	t_lex	*after_end;

	before_start = NULL;
	after_end = NULL;
	if ((*start)->prev)
		before_start = (*start)->prev;
	if ((*end)->next)
		after_end = (*end)->next;
	if (before_start)
		before_start->next = after_end;
	if (after_end)
		after_end->prev = before_start;
	(*start)->prev = NULL;
	(*end)->next = NULL;
	return (before_start);
}

void	attach_redir_node(t_redir **redir_info, t_lex **before_start)
{
	t_token	*tok;
	t_lex	*redir_node;

	tok = create_token("redir", REDIR);
	redir_node = new_redir_node(&tok, redir_info);
	if (*before_start)
		dllinsafter(before_start, &redir_node);
	clean_inside_token(&tok);
}
