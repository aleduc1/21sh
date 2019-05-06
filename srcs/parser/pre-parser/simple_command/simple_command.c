#include "lexer.h"

void	simple_command(t_lex **head)
{
	t_lex	*start;
	t_lex	*end;
	t_token	*token;
	t_lex	*node;

	// Assign start and end pointer at head
	set_delim(head, &start, &end);

	// Set start on the first node we want, and end after the last node we want
	while (identify_delim(&start, &end))
	{
		// Detach the DLL to make it unrelated to the whole lexer, ending with a NULL ptr
		detach(&start, &end);

		// Create a command token with the standalone DLL inside
		token = create_command_token(&start, CMD);

		// Create a node containing the command's token
		node = new_node(&token);

		// Link node to the Lexer DLL
		attach(head, &node, &end);

		// The only thing to free, I didnt assign during new_node but duplicated so it works, no memory error after freeing the token
		ft_strdel(&token->data);
		ft_memdel((void **)&token);

		// Reset start and end to do another iteration of the loop
		set_delim(head, &start, &end);
	}
}
