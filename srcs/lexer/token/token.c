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
	return (token);
}

t_token		*CreateCommandToken(t_lex **command, t_type types)
{
	t_token	*token;

	token = NULL;
	if (!(token = (t_token *)ft_memalloc(sizeof(token))))
		return (NULL);
	token->data = ft_strdup("Command");
	token->command = *command;
	if (!token->data)
	{
		free(token);
		return (NULL);
	}
	token->type = types;
	return (token);
}
