/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 08:43:53 by sbelondr          #+#    #+#             */
/*   Updated: 2019/04/12 11:39:26 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "env.h"
#include "../../includes/env.h"

/*
** fd_stock[0] -> in
** fd_stock[1] -> out
** fd_stock[2] -> error
*/

int		add_process(char **command, int fd_stock[3], t_env *my_env,
		int *returns_code)
{
	char	**env;
	int		pid;

	if (is_in_path(&command, my_env) != 1)
		return (-1);
	env = create_list_env(my_env, 0);
	pid = fork();
	waitpid(pid, &(*returns_code), 0);
	if (pid == 0)
	{
		if (fd_stock[0] != 0)
			dup2(fd_stock[0], 0);
		if (fd_stock[1] != 1)
			dup2(fd_stock[1], 1);
		if (fd_stock[2] != 2)
			dup2(fd_stock[2], 2);
		execve(command[0], command, env);
		ft_dprintf(2, "21sh: %s: No such file or directory\n", command[0]);
		exit(pid);
	}
	ft_arraydel(&env);
	return (pid);
}

int		exec_fork(char **command, t_env **my_env, int fd_stock[3])
{
	int	return_code;
	int	pid;
//	int	fd_stock[3];

//	fd_stock[0] = 0;
//	fd_stock[1] = dest_output(&(*my_env));
//	fd_stock[2] = dest_error_output(&(*my_env));
	signal(SIGINT, NULL);
	pid = add_process(command, fd_stock, *my_env, &return_code);
//	close_file(&(*my_env));
//	close_error_file(&(*my_env));
	if (pid != -1)
		kill(pid, SIGINT);
	return (return_code);
}
/*
int		exec_pipe_fork(char **command, char **command_bis, char **env,
		t_env **my_env)
{
	int	return_code;
	int	pids[2];
	int	pipes[2];
	int	fd_stock[3];

	pipe(pipes);
	fd_stock[0] = 0;
	fd_stock[1] = pipes[1];
	fd_stock[2] = dest_error_output(&(*my_env));
	pids[0] = add_process(command, fd_stock, env, &return_code);
	close(pipes[1]);
	fd_stock[0] = pipes[0];
	fd_stock[1] = dest_output(&(*my_env));
	pids[1] = add_process(command_bis, fd_stock, env, &return_code);
	close(fd_stock[0]);
	close_file(&(*my_env));
	close_error_file(&(*my_env));
	return (return_code);
}

int		exec_pipe(char **command, t_env **my_env, char **env)
{
	char	**part_array;
	char	**tmp;
	int		i;

	i = 0;
	while (ft_strequ(command[i], "|") == 0)
		i++;
	part_array = ft_arraysub(command, 0, i);
	tmp = ft_arraysub(command, i + 1, ft_arraylen(command));
	is_in_path(&tmp, *my_env);
	i = exec_pipe_fork(part_array, tmp, env, &(*my_env));
	ft_arraydel(&tmp);
	ft_arraydel(&part_array);
	free_maillon_env(&(*my_env), "PIPE", 0);
	return (i);
}

int		exec_command(t_arg *lst_arg, t_env **my_env)
{
	int		verif;
	char	**env;
	char	**command;

	env = create_list_env(*my_env, 0);
	command = transfer_arg(lst_arg);
	verif = is_builtin(lst_arg, &(*my_env));
	if (verif == 0)
	{
		if (command[0] && is_in_path(&command, *my_env) == 1)
		{
			if (search_line_env(*my_env, "PIPE", 0) == 1)
				verif = exec_pipe(command, &(*my_env), env);
			else
				verif = exec_fork(command, &(*my_env), env);
		}
		else
			ft_dprintf(2, "21sh: Command not found\n");
	}
	ft_arraydel(&command);
	ft_arraydel(&env);
	gest_return(verif, &(*my_env));
	return (verif);
}*/
