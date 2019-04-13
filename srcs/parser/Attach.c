#include "lexer.h"

/*
** Detach the part of the DLL that will go into the token command
*/

void	Detach(t_lex **start, t_lex **end)
{
	t_lex *BeforeStart;
	t_lex *BeforeEnd;

	BeforeStart = (*start)->prev;
	BeforeEnd = (*end)->prev;
	BeforeStart->next = NULL;
	BeforeEnd->next = NULL;
	(*start)->prev = NULL;
	(*end)->prev = NULL;
}

/*
** Link the node's command token to the lexer
*/

void	Attach(t_lex **head, t_lex **node, t_lex **end)
{
	t_lex	*ptr;

	ptr = dlllastnode(head);
	ptr->next = *node;
	(*end)->prev = *node;
	(*node)->prev = ptr;
	(*node)->next = *end;
}
