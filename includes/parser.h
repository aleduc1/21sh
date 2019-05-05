#ifndef PARSER_H
# define PARSER_H

#include "sh21.h"
#include "lexer.h"

# define OPERATORS (t->type == SCOLON || t->type == SPIPE )

typedef struct     s_ast
{
	t_token        *token;
	struct s_ast   *l;
	struct s_ast   *r;
}                  t_ast;

typedef struct      s_args
{
	char            *arg;
	struct s_args   *prev;
	struct s_args   *next;
}                   t_args;

typedef struct      s_std
{
	int             fd; // default depending on std[x], -1 if filename on.
	char            *filename; // NULL if fd.
	int             append; // 0 no, 1 yes.
}                   t_std;

typedef struct      s_cmd
{
	int		        in;
	int           	out;
	int           	err;
	char            **argv;
	char            *heredoc; // NULL or raw string.
}                   t_cmd;

t_ast               *node_ast(t_token *token, t_ast *l, t_ast *r);
void                pretty_print(t_ast *tree);
void                ast_print(t_ast *root, int space);

t_ast               *expr(int rbp);
t_ast               *ast_parser(t_lex *tokens);


t_cmd               *run(t_lex *cmd_list);

#endif
