#include "lexer.h"

void	dllprinthead(t_lex **head)
{
	t_lex	*ptr;

	ptr = *head;
	while (ptr)
	{
		ft_putendl(ptr->token->data);
		if (ptr->token->type == CMD )
		{
			ft_putendl("\nIn this Command token there is this DLL : ");
			dllprinthead(&ptr->token->command);
			ft_putendl("Back to the Lexer DLL, after the command token there is : \n");
		}
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

t_lex	*dlllastnode(t_lex **head)
{
	t_lex	*ptr;

	ptr = *head;
	while (ptr->next)
		ptr = ptr->next;
	return (ptr);
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
