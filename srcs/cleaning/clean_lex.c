/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_lex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 15:18:28 by aleduc            #+#    #+#             */
/*   Updated: 2019/05/04 02:53:15 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "lexer.h"

void	clean_inside_token(t_token **token)
{
/*	if (token && (*token))
	{
		clean_lex(&((*token)->command));
		ft_strdel(&((*token)->data));
		free(*token);
		(*token) = NULL;
	}*/
	t_token	*ptr;

		ft_putchar('+');
		ft_putendl(ptr->data);
	ptr = *token;
	ptr->type = 0;
	ptr->command = NULL;
//	if (ptr->data[0])
		ft_strdel(&ptr->data);
}

void	clean_lex(t_lex **lex)
{
/*	if ((!lex) || (!(*lex)))
		return ;

	if ((*lex)->next)
		clean_lex(&(*lex)->next);
	clean_inside_token(&(*lex)->token);
	free((*lex));
	(*lex) = NULL;*/
	t_lex	*ptr;
	t_lex	*tmp;

	tmp = NULL;
	ptr = *lex;
	while (ptr)
	{
		tmp = ptr;
		if (ptr->token->command)
			clean_lex(&ptr->token->command);
		clean_inside_token(&ptr->token);
		if (ptr->token)
			ft_memdel((void**)&ptr->token);
		ptr = ptr->next;
		dll_del_node(&tmp);
	}
}
