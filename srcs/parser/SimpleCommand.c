#include "lexer.h"

void	SimpleCommand(t_lex **head)
{
	t_lex	*start;
	t_lex	*end;
	t_token	*token;
	t_lex	*node;

	// Assign start and end pointer at head
	SetDelim(head, &start, &end);

	// Set start on the first node we want, and end after the last node we want
	while (IdentifyDelim(&start, &end))
	{
		// Detach the DLL to make it unrelated to the whole lexer, ending with a NULL ptr
		Detach(&start, &end);

		// Create a command token with the standalone DLL inside
		token = CreateCommandToken(&start, CMD);

		// Create a node containing the command's token
		node = new_node(&token);

		// Link node to the Lexer DLL
		Attach(head, &node, &end);

		// The only thing to free, I didnt assign during new_node but duplicated so it works, no memory error after freeing the token
		ft_memdel((void **)&token);

		// Reset start and end to do another iteration of the loop
		SetDelim(head, &start, &end);
	}
}
