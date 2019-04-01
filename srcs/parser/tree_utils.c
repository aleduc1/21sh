#include "sh21.h"
#include "lexer.h"
#include "parser.h"

char    depth[2056];
int     di;

void print_push(char c)
{
    depth[di++] = ' ';
    depth[di++] = c;
    depth[di++] = ' ';
    depth[di++] = ' ';
    depth[di] = 0;
}

void pretty_print(t_ast *tree)
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

void ast_print(t_ast *root, int space)
{
    if (root == NULL) 
        return;
    space += 4;
    ast_print(root->r, space);
    for (int i = 4; i < space; i++) 
        printf(" ");
    printf("[%s]\n", root->token->data);
    ast_print(root->l, space); 
}

t_ast *node_ast(t_token *token, t_ast *l, t_ast *r)
{
    t_ast *node;
    
    node = (t_ast *)malloc(sizeof(t_ast));
    node->token = token;
    node->l = l;
    node->r = r;
    return(node);
}