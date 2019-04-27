/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 08:43:53 by sbelondr          #+#    #+#             */
/*   Updated: 2019/04/27 11:48:01 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "env.h"
#include "../../includes/env.h"

/*
** in -> STDIN_FILENO
** out -> STDOUT_FILENO
** error -> STDERR_FILLENO
*/

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
		ft_dprintf(2, "21sh: %s: No such file or directory\n", cmd->argv[0]);
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
