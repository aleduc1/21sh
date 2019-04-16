/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_lex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 15:18:28 by aleduc            #+#    #+#             */
/*   Updated: 2019/04/16 16:25:50 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	clean_inside_token(t_token **token)
{
	t_token	*ptr;

	ptr = *token;
	ptr->type = 0;
	if (ptr->data[0])
	{
		free(ptr->data);
		ptr->data = NULL;
	}
}

void	clean_lex(t_lex **lex)
{
	t_lex	*ptr;
	t_lex	*tmp;

	tmp = NULL;
	ptr = *lex;
	while (ptr)
	{
		tmp = ptr;
		if (ptr->token->command)
			clean_lex(&ptr->token->command);
		ptr->token->command = NULL;
		clean_inside_token(&ptr->token);
		ft_memdel((void**)&ptr->token);
		ptr = ptr->next;
		dll_del_node(&tmp);
	}
}
