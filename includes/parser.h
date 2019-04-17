#ifndef PARSER_H
# define PARSER_H

#include "sh21.h"
#include "lexer.h"

# define OPERATORS (t->type == SCOLON || \
                    t->type == SPIPE || t->type == DPIPE || \
                    t->type == DAMPERSAND || t->type == DELIM)

typedef struct     s_ast
{
    t_token        *token;
    struct s_ast   *l;
    struct s_ast   *r;    
}                  t_ast;

t_ast               *node_ast(t_token *token, t_ast *l, t_ast *r);
void                pretty_print(t_ast *tree);
void                ast_print(t_ast *root, int space);

t_ast               *expr(int rbp);
t_ast               *ast_parser(t_lex *tokens);






//CMD PARSER

# define NEXT (*cursor) = (*cursor)->next;
# define CURRENT_DATA(x) ((*cursor)->token->data == (x))
# define CURRENT_TYPE(x) ((*cursor)->token->type == (x))
# define PEEK_DATA(x) ((*cursor)->next->token->data == (x))
# define PEEK_TYPE(x) ((*cursor)->next->token->type == (x))
# define PEEK_OPERATORS (PEEK_TYPE(GREAT) || PEEK_TYPE(GREATAMP) || PEEK_TYPE(AMPGREAT) || \
         PEEK_TYPE(LESS) || PEEK_TYPE(LESSAMP) || PEEK_TYPE(AMPLESS) || \
         PEEK_TYPE(GREATAMPHYPH) || PEEK_TYPE(LESSAMPHYPH))

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
    t_std           in;
    t_std           out;
    t_std           err;
    t_args          **argv;
    char            *heredoc; // NULL or raw string.
}                   t_cmd;

t_cmd               cmd_parser(t_lex *cmd_list);

#endif
