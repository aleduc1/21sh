#include "parser.h"

void                dpush_args(t_args **head, char *arg) 
{ 
    t_args          *new_node;

    new_node = (t_args*)malloc(sizeof(t_args));  
    new_node->arg = ft_strdup(arg);  
    new_node->next = (*head);  
    new_node->prev = NULL;  
    if ((*head) != NULL)  
        (*head)->prev = new_node;  
    (*head) = new_node;
}

void init_std(t_std std, int fd, char *filename, int append)
{
    std.fd = fd;
    std.filename = filename;
    std.append = append;
}

void init_cmd(t_cmd *cmd)
{
    init_std(cmd->in, 0, NULL, 0);
    init_std(cmd->out, 1, NULL, 0);
    init_std(cmd->err, 2, NULL, 0);
    cmd->argv = NULL;
    cmd->heredoc = NULL;
}











// void push_fd(t_cmd *cmd, int io, int dest_fd, char *dest_file)
// {

// }

// void number_prefix(t_cmd *cmd, t_lex **cursor, t_args **args)
// {
//         if (CURRENT_DATA(0))
//             push_fd(cmd, 0);
//         else if (CURRENT_DATA(1))
//         else if (CURRENT_DATA(2))
// }

// void do_great(t_cmd *cmd, t_lex **cursor, t_args **args_lst)
// {
//     if(CURRENT_TYPE(NUMBER))
//     {
        
//     }
//     else if(CURRENT_TYPE(WORD))
//     else ERROR;
        
// }

// void           automata(t_cmd *cmd, t_lex **cursor, t_args **args_lst)
// {
//     while(*cursor)
//     {
//         if(PEEK_TYPE(GREAT))

//     }
    
    
//     // if(TYPE(NUMBER))
//     // {

//     // }
//     (void)args_lst;
//     (void)cmd;
// }

// t_cmd           cmd_parser(t_lex *cmd_lst)
// {
//     t_lex       *cursor;
//     t_args      *args_lst = NULL;
//     t_cmd       cmd;

//     cursor = cmd_lst;
//     init_cmd(&cmd);

//     automata(&cmd, &cursor, &args_lst);

//     t_args *argcursor = args_lst;
//     while(argcursor->next)
//         argcursor = argcursor->next;
//     while(argcursor)
//     {
//         printf("%s ", argcursor->arg);
//         argcursor = argcursor->prev;
//     }
//     printf("\n");
//     return(cmd);
// }