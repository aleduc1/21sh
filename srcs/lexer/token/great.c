/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   great.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 17:22:08 by aleduc            #+#    #+#             */
/*   Updated: 2019/04/03 17:33:42 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token		*great(void)
{
	t_token	*token;

	token = NULL;
	if (!(token = (t_token *)ft_memalloc(sizeof(token))))
		return (NULL);
	token->cmd = NULL;
	token->data = ft_strdup(">");
	if (!token->data)
	{
		free(token);
		return (NULL);
	}
	token->type = GREAT;
	ft_putnbr(token->type);			/*		DEBUGGING		*/
	ft_putendl(token->data);		/*		DEBUGGING		*/
	return (token);
}

t_token		*dgreat(void)
{
	t_token	*token;

	token = NULL;
	if (!(token = (t_token *)ft_memalloc(sizeof(token))))
		return (NULL);
	token->cmd = NULL;
	token->data = ft_strdup(">>");
	if (!token->data)
	{
		free(token);
		return (NULL);
	}
	token->type = DGREAT;
	ft_putnbr(token->type);			/*		DEBUGGING		*/
	ft_putendl(token->data);		/*		DEBUGGING		*/
	return (token);
}

t_token		*greatpipe(void)
{
	t_token	*token;

	token = NULL;
	if (!(token = (t_token *)ft_memalloc(sizeof(token))))
		return (NULL);
	token->cmd = NULL;
	token->data = ft_strdup(">|");
	if (!token->data)
	{
		free(token);
		return (NULL);
	}
	token->type = GREATPIPE;
	ft_putnbr(token->type);			/*		DEBUGGING		*/
	ft_putendl(token->data);		/*		DEBUGGING		*/
	return (token);
}

t_token		*greatamp(void)
{
	t_token	*token;

	token = NULL;
	if (!(token = (t_token *)ft_memalloc(sizeof(token))))
		return (NULL);
	token->cmd = NULL;
	token->data = ft_strdup(">&");
	if (!token->data)
	{
		free(token);
		return (NULL);
	}
	token->type = GREATAMP;
	ft_putnbr(token->type);			/*		DEBUGGING		*/
	ft_putendl(token->data);		/*		DEBUGGING		*/
	return (token);
}

t_token		*lessgreat(void)
{
	t_token	*token;

	token = NULL;
	if (!(token = (t_token *)ft_memalloc(sizeof(token))))
		return (NULL);
	token->cmd = NULL;
	token->data = ft_strdup("<>");
	if (!token->data)
	{
		free(token);
		return (NULL);
	}
	token->type = LESSGREAT;
	ft_putnbr(token->type);			/*		DEBUGGING		*/
	ft_putendl(token->data);		/*		DEBUGGING		*/
	return (token);
}
