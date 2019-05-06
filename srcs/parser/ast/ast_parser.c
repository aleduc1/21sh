#include "lexer.h"
#include "sh21.h"
#include "parser.h"

t_token			*next()
{
	stream =	(stream->next) ? stream->next : stream;
	return (stream) ? (stream->token) : (NULL);
}

t_token			*peek()
{
	return (stream->next) ? (stream->next->token) : (NULL);
}

int				bp(t_token *token)
{
	if(token == NULL)
		return (0);
	else if(token->type == DELIM)
		return (-10);
	else if(token->type == CMD)
		return (10);
	else if(token->type == SCOLON)
		return (20);
	else if(token->type == SPIPE)
		return (30);
	else
		return (0);
}

t_ast			*nud(t_token *t)
{
	if (t->type == CMD)
		return (node_ast(t, NULL, NULL));
	else if (OPERATORS)
	{
		ft_putstr("21sh: parse error near: ");
		ft_putendl(t->data);
		get_out = 1;
		return (node_ast(t, NULL, NULL));
	}
	else
		return (NULL);
}

t_ast			*led(t_ast *left, t_token *t)
{
	if (t->type == SCOLON)
		return (node_ast(t, left, expr(20)));
	else if (t->type == SPIPE)
		return (node_ast(t, left, expr(30)));
	else if (t->type == CMD || t->type == DELIM)
	{
		ft_putstr("21sh: parse error near: ");
		ft_putendl(t->data);
		get_out = 1;
		return (left);
	}
	else
		return (NULL);
}

t_ast			*expr(int rbp)
{
	t_ast		*left;

	left = NULL;
	if(get_out == 1)
		return (left);
	left = nud(next());
	while (rbp < bp(peek()))
		left = led(left, next());
	return (left);
}
