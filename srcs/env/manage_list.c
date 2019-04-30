/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 10:50:50 by sbelondr          #+#    #+#             */
/*   Updated: 2019/04/30 09:38:58 by sbelondr         ###   ########.fr       */
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

int		ft_pipe(t_cmd *cmds, int nb, t_env **my_env)
{
	int	i;
	int	return_code;
	int	pids[nb];
	int	pipes[2];

	i = -1;
	while (++i < (nb - 1))
	{
		pipe(pipes);
		cmds->out->fd = choice_fd(cmds->out->fd, pipes[1], 1);
		if ((pids[i] = is_builtin(cmds, &(*my_env))) == -1)
			pids[i] = add_process(cmds, *my_env, &return_code);
		close(pipes[1]);
		cmds = cmds->next;
		cmds->in->fd = pipes[0];
	}
	cmds->out->fd = choice_fd(cmds->out->fd, pipes[1], 1);
	if ((pids[i] = is_builtin(cmds, &(*my_env))) == -1)
		pids[i] = add_process(cmds, *my_env, &return_code);
	return (return_code);
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

	if (is_builtin(cmd, &(*my_env)) != -1)
		verif = 0;
	else
		verif = exec_fork(cmd, &(*my_env));
	close_file(&(*my_env));
	close_error_file(&(*my_env));
	return (verif);
}
