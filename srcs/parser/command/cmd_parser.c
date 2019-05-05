#include "parser.h"

int				get_argc(t_lex *cursor)
{
	int len;

	len = 0;
	while (cursor)
	{
		if(cursor->token->type == WORD || cursor->token->type == NUMBER)
			len++;
		ft_putstr(cursor->token->data);
		ft_putstr(" ->");
		cursor = cursor->next;
	}
	ft_putstr("\n");
	return (len);
}
char			**get_argv(t_lex *cmd_list)
{
	char **argv;
	t_lex *cursor;
	int len;
	int i;

	i = 0;
	cursor = cmd_list->next->token->command; // REMEMBER TO CHANGE IT SO IT MAKES SENSE IN THE INTERPRETER
	len = get_argc(cursor);
	if(!(argv = (char **)malloc(sizeof(char *) * len + 1)))
		return (NULL);
	while(cursor)
	{
		if(cursor->token->type == WORD || cursor->token->type == NUMBER)
			argv[i++] = ft_strdup(cursor->token->data);
		cursor = cursor->next;
	}
	return (argv);
}

void			files_handler(t_lex *cmd_list)
{
	t_lex *cursor;

	cursor = cmd_list->next->token->command;
	while(cursor)
	{
		if (cursor->token->type == REDIR)
				open_file_std(redir);
		cursor = cursor->next;
	}
}

void	open_redirection(t_cmd *cmd)
{
	if (cmd->in->fd != 0)
		dup2(cmd->in->fd, STDIN_FILENO);
	if (cmd->out->fd != 1)
		dup2(cmd->out->fd, STDOUT_FILENO);
	if (cmd->err->fd != 2)
		dup2(cmd->err->fd, STDERR_FILENO);
}

int		add_process(t_cmd *cmd, t_env *my_env, int *returns_code)
{
	char	**env;
	int		pid;

	if (is_in_path(&(cmd->argv), my_env) != 1)
	{
		*returns_code = -1;
		return (-1);
	}
	env = create_list_env(my_env, 0);
	pid = fork();
	waitpid(pid, &(*returns_code), 0);
	if (pid == 0)
	{

		open_redirection(cmd);
		execve(cmd->argv[0], cmd->argv, env);
		ft_dprintf(STDERR_FILENO, "21sh: command not found: %s\n", cmd->argv[0]);
		exit(pid);
	}
	ft_arraydel(&env);
	return (pid);
}

int		exec_fork(t_cmd *cmd, t_env **my_env)
{
	int	return_code;
	int	pid;

	signal(SIGINT, NULL);
	pid = add_process(cmd, *my_env, &return_code);
	if (pid != -1)
		kill(pid, SIGINT);
	return (return_code);
}

int		ft_simple_command(t_cmd *cmd)
{
	int		verif;

	if ((verif = is_builtin(cmd, &(*my_env))) == -1)
		verif = exec_fork(cmd, &(*my_env));
	close_file_command(cmd);
	gest_return(verif, &(*my_env));
	return (verif);
}

t_env 	*my_env(void)
{
	static t_env	*env;

	if (env == NULL)
		env = init_env();
	return (env);
}

int			*run(t_lex *cmd_list)
{
	char	**argv;

	argv = get_argv(cmd_list);
	files_handler(cmd_list);
	ft_simple_command(argv, cmd_list);
}

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
