/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 08:43:53 by sbelondr          #+#    #+#             */
/*   Updated: 2019/07/09 13:35:11 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

int			add_process(char **cmd, int *returns_code, t_redirection *r)
{
	char	**env;
	int		pid;
	char	*str;

	if (!(str = is_in_path(cmd[0])))
	{
		(*returns_code) = gest_error_path(cmd[0], r);
		return (*returns_code);
	}
	env = create_list_env(get_env(0, NULL), 1);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		redirection_fd(r);
		execve(str, cmd, env);
		gest_error_exec(cmd[0], r);
		execve("/bin/test", NULL, NULL);
		exit(pid);
	}
	ft_arraydel(&env);
	ft_strdel(&str);
	return (pid);
}

int			add_pipe_process(char **cmd, t_redirection *r)
{
	pid_t	pid;
	char	**environ;
	char	*str;

	str = is_in_path(cmd[0]);
	if (!str)
	{
		gest_return(gest_error_path(cmd[0], r));
		return (-1);
	}
	pid = fork();
	environ = create_list_env(get_env(0, NULL), 0);
	if (pid == 0)
	{
		sig_dfl();
		redirection_fd(r);
		execve(str, cmd, environ);
		gest_error_exec(cmd[0], r);
		execve("/bin/test", NULL, NULL);
		exit(0);
	}
	ft_arraydel(&environ);
	ft_strdel(&str);
	return (pid);
}

int			exec_fork(char **cmd, t_redirection *r)
{
	int	return_code;
	int	pid;

	signal(SIGINT, sighandler);
	signal(SIGQUIT, sighandler);
	pid = add_process(cmd, &return_code, r);
	while (wait(&return_code) != -1)
		continue ;
	if (pid != -1)
		kill(pid, SIGINT);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	return (return_code);
}

int			ft_simple_command_env(char **argv, t_redirection *r)
{
	int	verif;

	signal(SIGINT, sighandler);
	signal(SIGQUIT, sighandler);
	if ((verif = is_builtin(argv, r)) == -1)
	{
		if (r->fd_pipe == -1)
			verif = exec_fork(argv, r);
		else
			verif = add_pipe_process(argv, r);
	}
	return (verif);
}
