#include "parser.h"

// int				get_argc(t_lex *cursor)
// {
// 	int len;

// 	len = 0;
// 	while (cursor)
// 	{
// 		if(cursor->token->type == WORD || cursor->token->type == NUMBER)
// 			len++;
// 		ft_putstr(cursor->token->data);
// 		ft_putstr(" ->");
// 		cursor = cursor->next;
// 	}
// 	ft_putstr("\n");
// 	return (len);
// }
// char			**get_argv(t_lex *cmd_list)
// {
// 	char **argv;
// 	t_lex *cursor;
// 	int len;
// 	int i;

// 	i = 0;
// 	cursor = cmd_list->next->token->command; // REMEMBER TO CHANGE IT SO IT MAKES SENSE IN THE INTERPRETER
// 	len = get_argc(cursor);
// 	if(!(argv = (char **)malloc(sizeof(char *) * len + 1)))
// 		return (NULL);
// 	while(cursor)
// 	{
// 		if(cursor->token->type == WORD || cursor->token->type == NUMBER)
// 			argv[i++] = ft_strdup(cursor->token->data);
// 		cursor = cursor->next;
// 	}
// 	return (argv);
// }

// void			files_handler(t_lex *cmd_list, t_pos *pos)
// {
// 	t_lex *cursor;

// 	cursor = cmd_list->next->token->command;
// 	while(cursor)
// 	{
// 		if (cursor->token->type == REDIR)
// 				open_file_std(redir, pos);
// 		cursor = cursor->next;
// 	}
// }

// int			*run(t_lex *cmd_list, t_pos *pos)
// {
// 	char	**argv;

// 	argv = get_argv(cmd_list);
// 	files_handler(cmd_list, pos);
// 	ft_simple_command(argv, cmd_list);
// }

// void                dpush_args(t_args **head, char *arg)
// {
//     t_args          *new_node;

//     new_node = (t_args*)malloc(sizeof(t_args));
//     new_node->arg = ft_strdup(arg);
//     new_node->next = (*head);
//     new_node->prev = NULL;
//     if ((*head) != NULL)
//         (*head)->prev = new_node;
//     (*head) = new_node;
// }

// void init_std(t_std std, int fd, char *filename, int append)
// {
//     std.fd = fd;
//     std.filename = filename;
//     std.append = append;
// }











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
