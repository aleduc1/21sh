#include "lexer.h"

t_token		*create_token(char *str, t_type types)
{
	t_token	*token;

	token = NULL;
	if (!(token = (t_token *)ft_memalloc(sizeof(token))))
		return (NULL);
	token->data = ft_strdup(str);
	if (!token->data)
	{
		free(token);
		return (NULL);
	}
	token->type = types;
	ft_putnbr(token->type);			/*		DEBUGGING		*/
	ft_putendl(token->data);		/*		DEBUGGING		*/
	return (token);
}
