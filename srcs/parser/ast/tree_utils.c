#include "sh21.h"
#include "lexer.h"
#include "parser.h"

static char	depth[2056];
static int	di;

void		print_push(char c)
{
	depth[di++] = ' ';
	depth[di++] = c;
	depth[di++] = ' ';
	depth[di++] = ' ';
	depth[di] = 0;
}

void		pretty_print(t_ast *tree)
{
	ft_putchar('[');
	ft_putstr(tree->token->data);
	ft_putstr("]\n");

	if (tree->l)
	{
		ft_putstr(depth);
		ft_putstr(" ├──");
		print_push('|');
		pretty_print( tree->r);
		depth[di -= 4] = 0;

		ft_putstr(depth);
		ft_putstr(" └──");
		print_push(' ');
		pretty_print(tree->l);
		depth[di -= 4] = 0;
	}
}

t_ast		*node_ast(t_token *token, t_ast *l, t_ast *r)
{
	t_ast	*node;

	node = (t_ast *)malloc(sizeof(t_ast));
	node->token = token;
	node->l = l;
	node->r = r;
	return(node);
}

void		clean_ast(t_ast *node)
{
	if (!node)
		return ;
	clean_ast(node->l);
	clean_ast(node->r);
	free(node);
	node = NULL;
}

t_ast		*ast_parser(t_lex *tokens)
{
	t_ast	*ast;

	get_out = 0;
	stream = tokens;
	ast = expr(0);
	if(get_out == 1)
	{
		clean_ast(ast);
		return (NULL);
	}
	ft_putstr("---------------AST---------------\n");
	pretty_print(ast);
	ft_putstr("---------------------------------\n");
	return (ast);
}
