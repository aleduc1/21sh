#include "lexer.h"

t_token		*less(void)
{
	t_token	*token;

	token = NULL;
	if (!(token = (t_token *)ft_memalloc(sizeof(token))))
		return (NULL);
	token->data = ft_strdup("<");
	if (!token->data)
	{
		free(token);
		return (NULL);
	}
	token->type = LESS;
	ft_putnbr(token->type);			/*		DEBUGGING		*/
	ft_putendl(token->data);		/*		DEBUGGING		*/
	return (token);
}

t_token		*dless(void)
{
	t_token	*token;

	token = NULL;
	if (!(token = (t_token *)ft_memalloc(sizeof(token))))
		return (NULL);
	token->data = ft_strdup("<<");
	if (!token->data)
	{
		free(token);
		return (NULL);
	}
	token->type = DLESS;
	ft_putnbr(token->type);			/*		DEBUGGING		*/
	ft_putendl(token->data);		/*		DEBUGGING		*/
	return (token);
}

t_token		*lessamp(void)
{
	t_token	*token;

	token = NULL;
	if (!(token = (t_token *)ft_memalloc(sizeof(token))))
		return (NULL);
	token->data = ft_strdup("<&");
	if (!token->data)
	{
		free(token);
		return (NULL);
	}
	token->type = LESSAMP;
	ft_putnbr(token->type);			/*		DEBUGGING		*/
	ft_putendl(token->data);		/*		DEBUGGING		*/
	return (token);
}

t_token		*dlesshyph(void)
{
	t_token	*token;

	token = NULL;
	if (!(token = (t_token *)ft_memalloc(sizeof(token))))
		return (NULL);
	token->data = ft_strdup("<<-");
	if (!token->data)
	{
		free(token);
		return (NULL);
	}
	token->type = DLESSHYPH;
	ft_putnbr(token->type);			/*		DEBUGGING		*/
	ft_putendl(token->data);		/*		DEBUGGING		*/
	return (token);
}
