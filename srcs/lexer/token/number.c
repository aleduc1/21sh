/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numbers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 18:27:21 by aleduc            #+#    #+#             */
/*   Updated: 2019/03/18 18:36:45 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token		*number(char *numbers)
{
	t_token	*token;

	token = NULL;
	if (!(token = (t_token *)ft_memalloc(sizeof(token))))
		return (NULL);
	token->data = ft_strdup(numbers);
	if (!token->data)
	{
		free(token);
		return (NULL);
	}
	token->type = NUMBER;
	ft_putnbr(token->type);			/*		DEBUGGING		*/
	ft_putendl(token->data);		/*		DEBUGGING		*/
	return (token);
}
