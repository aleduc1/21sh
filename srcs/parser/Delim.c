#include "lexer.h"

void	SetDelim(t_lex **head, t_lex **start, t_lex **end)
{
	*start = *head;
	*end = *head;
}

void	SetEnd(t_lex **end)
{
	while (*end && TypeToEndOn((*end)->token->type))
		*end = (*end)->next;
}

void	SetStart(t_lex **start)
{
	while (*start && TypeToIgnore((*start)->token->type))
		*start = (*start)->next;
}

t_lex	*IdentifyDelim(t_lex **start, t_lex **end)
{
	SetStart(start);
	*end = *start;
	SetEnd(end);
	return (*start);
}
