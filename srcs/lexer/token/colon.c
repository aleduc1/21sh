#include "lexer.h"

t_token		*scolon(void)
{
	t_token	*token;

	token = NULL;
	if (!(token = (t_token *)ft_memalloc(sizeof(token))))
		return (NULL);
	token->data = ft_strdup(";");
	if (!token->data)
	{
		free(token);
		return (NULL);
	}
	token->type = SCOLON;
	ft_putnbr(token->type);			/*		DEBUGGING		*/
	ft_putendl(token->data);		/*		DEBUGGING		*/
	return (token);
}

t_token		*dscolon(void)
{
	t_token	*token;

	token = NULL;
	if (!(token = (t_token *)ft_memalloc(sizeof(token))))
		return (NULL);
	token->data = ft_strdup(";;");
	if (!token->data)
	{
		free(token);
		return (NULL);
	}
	token->type = DSCOLON;
	ft_putnbr(token->type);			/*		DEBUGGING		*/
	ft_putendl(token->data);		/*		DEBUGGING		*/
	return (token);
}
