/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_less.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 19:36:08 by aleduc            #+#    #+#             */
/*   Updated: 2019/05/04 20:10:46 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	start_grammar_less(t_lex **start)
{
	if ((*start)->prev->token->type == NUMBER)
		(*start) = (*start)->prev;
}

void	end_grammar_less(t_lex **start, t_lex **end, t_type type_check)
{
	(*end) = (*start);
	(*end) = (*end)->next;
	if ((*end) && (*end)->token->type == type_check && (*end)->next)
		(*end) = (*end)->next;
	if (((*end)->token->type == SPACE) && ((*end)->next))
		(*end) = (*end)->next;
}
