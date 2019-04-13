#include "lexer.h"
#include "sh21.h"
#include "parser.h"

static t_lex   *lstcursor;

t_token *next()
{
    lstcursor = lstcursor->next;
    return(lstcursor->token);
}

t_token *peek()
{
    return(lstcursor->next->token);
}

int bp(t_token *token)
{
    if(token->type == DELIM)
        return (-100);
    else if(token->type == CMD)
        return (10);
    else if(token->type == SCOLON)
        return (20);
    else if(token->type == DAMPERSAND || token->type == DPIPE) 
        return (25);
    else if(token->type == SPIPE)
        return (30);
    else
        return (0);
}

t_ast *nud(t_token *t)
{
    if (t->type == CMD)
        return (node_ast(t, NULL, NULL));
    else if (OPERATORS)
    {
        ft_putstr("21sh: parse error near: ");
        ft_putendl(t->data);
        exit (1);
    }
    else
        return (NULL);
}

t_ast *led(t_ast *left, t_token *t)
{
    if (t->type == SCOLON)
        return (node_ast(t, left, expr(20, left)));
    else if (t->type == DPIPE || t->type == DAMPERSAND)
        return (node_ast(t, left, expr(25, left)));
    else if (t->type == SPIPE)
        return (node_ast(t, left, expr(30, left)));
    else if (t->type == CMD)
    {
        ft_putstr("21sh: parse error near: ");
        ft_putendl(t->data);
        exit (1);
    }
    else
        return (NULL);
    
}

t_ast *expr(int rbp, t_ast *left)
{
    left = nud(next());
    while (rbp < bp(peek()))
    {
        left = led(left, next());
    }
    return (left);
}

t_ast     *parser(t_lex *tokens)
{
    t_ast *ast;
    // t_lex *lstcursor;
    lstcursor = tokens;
    ast = expr(0, NULL);
    ft_putstr("---------------AST---------------\n");
    pretty_print(ast);
    ft_putstr("---------------------------------\n");

    return (ast);
}