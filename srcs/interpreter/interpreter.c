#include "parser.h"

int		panic()
{
    printf("Fatal error: AST not found by interpreter.");
    return (-1);
}

int			*solo_tree(t_ast *node, t_pos *pos)
{
	if(node->token->type == CMD)
	{
		run_cmd(node->token, pos);
		return (1);
	}
	else
		return (-1);

}
t_token 	*interpreter(t_ast *node, t_pos *pos)
{
	// run_pipe(node->l->token, pos, 0);
	// run_pipe(node->r->token, pos, 1);
	if (!node)
		return (panic());
	if(node->token->type == SPIPE)
	{
		run_pipe(node->l->token, pos, 0);
		if(node->r->token->type != SPIPE || node->r->token->type != SCOLON)
			run_pipe(node->r->token, pos, 1);
		else
			run_pipe(node->r->token, pos, 0);
		return (NULL);
	}
	interpreter(node->l, pos);
	interpreter(node->r, pos);

	return (0);
}
