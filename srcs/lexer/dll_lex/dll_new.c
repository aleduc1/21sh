/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 13:46:00 by aleduc            #+#    #+#             */
/*   Updated: 2019/05/04 14:00:55 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
 * Token need to be allocated before the call to this function
 * Then this functions only copy content to another token inside the DLL
 * So we can free the token sent after this call
*/

t_lex	*new_node(t_token **tok)
{
	t_lex	*node;

	node = NULL;
	if (!(node = (t_lex *)malloc(sizeof(t_lex))))
		return (NULL);
	node->token = (t_token *)ft_memalloc(sizeof(t_token));
	if (!node->token)
		node->token = NULL;
	else
	{
		node->token->data = ft_strdup((*tok)->data);
		node->token->command = (*tok)->command;
		node->token->type = (*tok)->type;
	}
	node->redir = NULL;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

t_lex	*new_redir_node(t_token **tok, t_redir **redir_info)
{
	t_lex	*node;

	node = NULL;
	if (!(node = (t_lex *)malloc(sizeof(t_lex))))
		return (NULL);
	node->token = (t_token *)ft_memalloc(sizeof(t_token));
	if (!node->token)
		node->token = NULL;
	else
	{
		node->token->data = ft_strdup((*tok)->data);
		node->token->command = (*tok)->command;
		node->token->type = (*tok)->type;
	}
	node->redir = *redir_info;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}
