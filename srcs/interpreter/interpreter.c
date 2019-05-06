#include "parser.h"

int		panic()
{
    printf("Fatal error: AST not found by interpreter.");
    return (-1);
}

int		solo_tree(t_ast *node, t_pos *pos)
{
	if(node->token->type == CMD)
	{
		run_cmd(node->token, pos);
		return (1);
	}
	else
		return (-1);
}

int		interpreter(t_ast *node, t_pos *pos)
{
	// run_pipe(node->l->token, pos, 0);
	// run_pipe(node->r->token, pos, 1);
	if (!node)
		return (panic());
	if(node->token->type == SPIPE)
	{
		run_pipe(node->l->token, pos, 0);
		if(node->r->token->type != SPIPE)
			run_pipe(node->r->token, pos, 1);
		return (0);
	}
	interpreter(node->l, pos);
	interpreter(node->r, pos);

	return (0);
}
