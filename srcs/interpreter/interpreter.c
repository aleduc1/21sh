#include "parser.h"

int		panic()
{
    printf("Fatal error: AST not found by interpreter.");
    return (-1);
}

int interpreter(t_ast *node)
{
    if (!node)
        panic();
    if(!node->l && !node->r)
        return(node);
    t_ast *l = interpreter(node->l);
    t_ast *r = interpreter(node->r);

    if (node->token->type == PIPE)
    {
        if (l == PIPE || r == PIPE)
            return (ft_pipe(parse_command(cmd));
        else
            return (ft_pipe((cmd->is_end = 1, parse_command(cmd)));
    }
    else if (node->data == '-')
        return (l-r);
    else if (node->data == '*')
        return (l*r);
    else if (node->data == '%')
        return (l%r);
    else if (node->data == '/')
        return (l*r);
    return (0);
}
