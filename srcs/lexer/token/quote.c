#include "lexer.h"

t_token		*squote(void)
{
	t_token	*token;

	token = NULL;
	if (!(token = (t_token *)ft_memalloc(sizeof(token))))
		return (NULL);
	token->data = ft_strdup("'");
	if (!token->data)
	{
		free(token);
		return (NULL);
	}
	token->type = SQUOTE;
	ft_putnbr(token->type);			/*		DEBUGGING		*/
	ft_putendl(token->data);		/*		DEBUGGING		*/
	return (token);
}

t_token		*dquote(void)
{
	t_token	*token;

	token = NULL;
	if (!(token = (t_token *)ft_memalloc(sizeof(token))))
		return (NULL);
	token->data = ft_strdup("\"");
	if (!token->data)
	{
		free(token);
		return (NULL);
	}
	token->type = DQUOTE;
	ft_putnbr(token->type);			/*		DEBUGGING		*/
	ft_putendl(token->data);		/*		DEBUGGING		*/
	return (token);
}

t_token		*tquote(void)
{
	t_token	*token;

	token = NULL;
	if (!(token = (t_token *)ft_memalloc(sizeof(token))))
		return (NULL);
	token->data = ft_strdup("`");
	if (!token->data)
	{
		free(token);
		return (NULL);
	}
	token->type = TQUOTE;
	ft_putnbr(token->type);			/*		DEBUGGING		*/
	ft_putendl(token->data);		/*		DEBUGGING		*/
	return (token);
}
