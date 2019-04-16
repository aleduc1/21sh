#include "lexer.h"

t_token		*create_token(char *str, t_type types)
{
	t_token	*token;

	token = NULL;
	if (!(token = (t_token *)ft_memalloc(sizeof(token))))
		return (NULL);
	token->data = ft_strdup(str);
	token->command = NULL;
	if (!token->data)
	{
		free(token);
		return (NULL);
	}
	token->type = types;
	ft_putnbr(token->type);
	ft_putendl(token->data);
	return (token);
}

t_token		*create_command_token(t_lex **command, t_type types)
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
	ft_putnbr(token->type);
	ft_putendl(token->data);
	return (token);
}
