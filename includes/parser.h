#ifndef PARSER_H
# define PARSER_H

#include "sh21.h"
#include "lexer.h"

t_lex				*stream;
int					get_out;

# define OPERATORS (t->type == SCOLON || t->type == SPIPE || t->type == DELIM)


typedef struct		s_ast
{
	t_token			*token;
	struct s_ast	*l;
	struct s_ast	*r;
}					t_ast;

void				pretty_print(t_ast *tree);
t_ast				*node_ast(t_token *token, t_ast *l, t_ast *r);
void				clean_ast(t_ast *node);

t_ast				*expr(int rbp);
t_ast				*ast_parser(t_lex *tokens);


int					*run(t_lex *cmd_list, t_pos *pos);

#endif
