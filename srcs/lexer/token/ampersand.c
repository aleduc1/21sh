#include "lexer.h"

t_token		*ampersand(void)
{
	t_token	*token;

	token = NULL;
	if (!(token = (t_token *)ft_memalloc(sizeof(token))))
		return (NULL);
	token->data = ft_strdup("&");
	if (!token->data)
	{
		free(token);
		return (NULL);
	}
	token->type = AMPERSAND;
	ft_putnbr(token->type);			/*		DEBUGGING		*/
	ft_putendl(token->data);		/*		DEBUGGING		*/
	return (token);
}

t_token		*dampersand(void)
{
	t_token	*token;

	token = NULL;
	if (!(token = (t_token *)ft_memalloc(sizeof(token))))
		return (NULL);
	token->data = ft_strdup("&&");
	if (!token->data)
	{
		free(token);
		return (NULL);
	}
	token->type = DAMPERSAND;
	ft_putnbr(token->type);			/*		DEBUGGING		*/
	ft_putendl(token->data);		/*		DEBUGGING		*/
	return (token);
}
