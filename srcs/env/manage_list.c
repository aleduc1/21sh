/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 10:50:50 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/03 20:29:30 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/env.h"

/*
** &
** num_process: processus en cours (le mettre a un 1 quand on appel
** ft_ampersand)
*/

int		background_process(t_cmd *cmds, t_env *my_env, int num_process)
{
	int	result;
	int	pid;

	pid = fork();
	if (pid > 0)
	{
		ft_printf("[%d] %d\n", num_process, pid);
		ft_ampersand(cmds->next, ++num_process, &(my_env));
	}
	waitpid(pid, &result, 0);
	if (pid == 0)
	{
		result = is_builtin(cmds, &my_env);
		if (result == -1)
			add_process(cmds, my_env, &result);
		execve("/bin/test", NULL, NULL);
		exit(pid);
	}
	return (pid);
}

int		ft_ampersand(t_cmd *cmds, int num_process, t_env **my_env)
{
	int	result;

	result = 0;
	if (cmds->next)
	{
		signal(SIGTTOU, NULL);
		result = background_process(cmds, *my_env, num_process);
		if (result != -1)
		{
			ft_printf("[%d] Done\t%s\n", num_process, cmds->argv[0]);
			kill(result, SIGTTOU);
		}
	}
	else
	{
		result = is_builtin(cmds, &(*my_env));
		if (result == -1)
			add_process(cmds, *my_env, &result);
	}
	return (result);
}

/*
** &&
*/

int		ft_ampersand_double(t_cmd *cmds, t_env **my_env)
{
	int	check;

	check = 0;
	while (cmds && check != -1 && check != 256)
	{
		check = ft_simple_command(cmds, &(*my_env));
		cmds = cmds->next;
	}
	return (check);
}

/*
** |
*/

int		choice_fd(int fd_base, int fd, int origin)
{
	int	stock_fd;

	if (origin == fd_base)
		stock_fd = fd;
	else
		stock_fd = fd_base;
	return (stock_fd);
}

int		ft_pipe_old(t_cmd *cmds, int nb, t_env **my_env)
{
	int	i;
	int	return_code;
	int	pids;
	int	pipes[2];

	i = -1;
	while (++i < (nb - 1))
	{
		open_file_command(cmds);
		pipe(pipes);
		cmds->out->fd = choice_fd(cmds->out->fd, pipes[1], 1);
		if ((pids = is_builtin(cmds, &(*my_env))) == -1)
			pids = add_process(cmds, *my_env, &return_code);
		close(pipes[1]);
		close_file_command(cmds);
		cmds = cmds->next;
		cmds->in->fd = pipes[0];
	}
	open_file_command(cmds);
	cmds->out->fd = choice_fd(cmds->out->fd, pipes[1], 1);
	if ((pids = is_builtin(cmds, &(*my_env))) == -1)
		pids = add_process(cmds, *my_env, &return_code);
	close_file_command(cmds);
	return (return_code);
}

int		ft_pipe(t_cmd *cmd, t_env **my_env)
{
	int	return_code;
	int	pids;
	int	pipes[2];

	if (cmd->end_pipe)
	{
		open_file_command(cmd);
		if ((return_code = is_builtin(cmd, &(*my_env))) == -1)
			pids = add_process(cmd, *my_env, &return_code);
		close_file_command(cmd);
		return (return_code);
	}
	else
	{
		open_file_command(cmd);
		pipe(pipes);
		cmd->out->fd = choice_fd(cmd->out->fd, pipes[1], 1);
		if ((pids = is_builtin(cmd, &(*my_env))) == -1)
			pids = add_process(cmd, *my_env, &return_code);
		close(pipes[1]);
		close_file_command(cmd);
		return (pipes[0]);
	}
	return (0);
}

/*
** ||
*/

int		ft_pipe_double(t_cmd *cmds, t_env **my_env)
{
	int	check;

	check = -1;
	while (cmds && (check == -1 || check == 256))
	{
		check = ft_simple_command(cmds, &(*my_env));
		cmds = cmds->next;
	}
	return (check);
}

/*
** simple command
*/

int		ft_simple_command(t_cmd *cmd, t_env **my_env)
{
	int		verif;

	open_file_command(cmd);
	if (is_builtin(cmd, &(*my_env)) != -1)
		verif = 0;
	else
		verif = exec_fork(cmd, &(*my_env));
	close_file_command(cmd);
	return (verif);
}
