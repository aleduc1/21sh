/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_rules_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 16:00:07 by aleduc            #+#    #+#             */
/*   Updated: 2019/05/05 13:28:24 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	start_grammar_great(t_lex **start)
{
	if ((*start)->prev->token->type == NUMBER)
		(*start) = (*start)->prev;
}

int		end_grammar_great(t_lex **start, t_lex **end, t_type type_check)
{
	(*end) = (*start);
	if ((*end)->next)
		(*end) = (*end)->next;
	else
	{
		ft_putendl("Syntax error near unexpected token after I/O redirect");
		return (1);
	}
	if ((*end) && (*end)->token->type == type_check && (*end)->next)
		(*end) = (*end)->next;
	if ((*end) && (*end)->token->type == type_check && !((*end)->next))
	{
		ft_putendl("Syntax error near unexpected token after I/O redirect");
		return (1);
	}
	if (((*end)->token->type == SPACE) && ((*end)->next))
		(*end) = (*end)->next;
	if ((*end)->token->type == SPACE && !((*end)->next))
	{
		ft_putendl("Syntax error near unexpected token after I/O redirect");
		return (1);
	}
	if ((*end)->token->type != NUMBER && (*end)->token->type != WORD)
	{
		ft_putendl("Syntax error near unexpected token after I/O redirect");
		return (1);
	}
	return (0);
}
