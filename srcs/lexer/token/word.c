/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 18:34:48 by aleduc            #+#    #+#             */
/*   Updated: 2019/03/18 18:37:40 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token		*word(char *words)
{
	t_token	*token;

	token = NULL;
	if (!(token = (t_token *)ft_memalloc(sizeof(token))))
		return (NULL);
	token->data = ft_strdup(words);
	if (!token->data)
	{
		free(token);
		return (NULL);
	}
	token->type = WORD;
	ft_putnbr(token->type);			/*		DEBUGGING		*/
	ft_putendl(token->data);		/*		DEBUGGING		*/
	return (token);
}
