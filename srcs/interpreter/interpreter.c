#include "parser.h"

int		panic()
{
    printf("Fatal error: AST not found by interpreter.");
    return (-1);
}

t_ast	*interpreter(t_ast *node, t_pos *pos)
{
    if(!node->l && !node->r)
       run(node->token, pos);
   
   // t_ast *l = interpreter(node->l, pos);
  // t_ast *r = interpreter(node->r, pos);

   
    return (0);
}
