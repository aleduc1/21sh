/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 08:43:53 by sbelondr          #+#    #+#             */
/*   Updated: 2019/04/15 11:47:39 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "env.h"
#include "../../includes/env.h"

/*
** fd_stock[0] -> in
** fd_stock[1] -> out
** fd_stock[2] -> error
*/

void	open_redirection(int fd_stock[3])
{
	if (fd_stock[0] != 0)
		dup2(fd_stock[0], STDIN_FILENO);
	if (fd_stock[1] != 1)
		dup2(fd_stock[1], STDOUT_FILENO);
	if (fd_stock[2] != 2)
		dup2(fd_stock[2], STDERR_FILENO);
}

int		add_process(char **command, int fd_stock[3], t_env *my_env,
		int *returns_code)
{
	char	**env;
	int		pid;

	if (is_in_path(&command, my_env) != 1)
	{
		*returns_code = -1;
		return (-1);
	}
	env = create_list_env(my_env, 0);
	pid = fork();
	waitpid(pid, &(*returns_code), 0);
	if (pid == 0)
	{
		open_redirection(fd_stock);
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

	signal(SIGINT, NULL);
	pid = add_process(command, fd_stock, *my_env, &return_code);
	if (pid != -1)
		kill(pid, SIGINT);
	return (return_code);
}
