#ifndef PARSER_H
# define PARSER_H

#include "sh21.h"
#include "lexer.h"

# define OPERATORS (t->type == SCOLON || \
                    t->type == SPIPE || \
                    t->type == GREAT || t->type == LESS || \
                    t->type == DGREAT || t->type == DLESS || \
                    t->type == DPIPE || t->type == DAMPERSAND)

typedef struct     s_ast
{
    t_token        *token;
    struct s_ast   *l;
    struct s_ast   *r;    
}                  t_ast;

t_ast              *node_ast(t_token *token, t_ast *l, t_ast *r);
void               pretty_print(t_ast *tree);
void               ast_print(t_ast *root, int space);

t_ast               *expr(int rbp, t_ast *left);
t_ast               *parser(t_lex *tokens);

#endif