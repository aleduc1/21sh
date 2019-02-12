#include "lexer.h"

t_token		*lbracket(void)
{
	t_token	*token;

	token = NULL;
	if (!(token = (t_token *)ft_memalloc(sizeof(token))))
		return (NULL);
	token->data = ft_strdup("[");
	if (!token->data)
	{
		free(token);
		return (NULL);
	}
	token->type = LBRACKET;
	ft_putnbr(token->type);			/*		DEBUGGING		*/
	ft_putendl(token->data);		/*		DEBUGGING		*/
	return (token);
}

t_token		*rbracket(void)
{
	t_token	*token;

	token = NULL;
	if (!(token = (t_token *)ft_memalloc(sizeof(token))))
		return (NULL);
	token->data = ft_strdup("]");
	if (!token->data)
	{
		free(token);
		return (NULL);
	}
	token->type = RBRACKET;
	ft_putnbr(token->type);			/*		DEBUGGING		*/
	ft_putendl(token->data);		/*		DEBUGGING		*/
	return (token);
}
