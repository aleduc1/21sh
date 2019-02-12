#include "lexer.h"

void	dllprinthead(t_lex **head)
{
	t_lex	*ptr;

	ptr = *head;
	while (ptr)
	{
		ft_putendl(ptr->token->data);
		ptr = ptr->next;
	}
}

void	dllprinttail(t_lex **tail)
{
	t_lex	*ptr;

	ptr = *tail;
	while (ptr->prev)
	{
		ft_putendl(ptr->token->data);
		ptr = ptr->prev;
	}
}

int		dlliter(t_lex **head)
{
	t_lex	*ptr;
	int		count;

	count = 0;
	ptr = *head;
	while (ptr)
	{
		count++;
		ptr = ptr->next;
	}
	return (count);
}
