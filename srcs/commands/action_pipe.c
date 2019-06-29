/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 10:50:50 by sbelondr          #+#    #+#             */
/*   Updated: 2019/06/02 18:20:30 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

static void	dup_pipe(int fd[2], int stock[2])
{
	if (stock[0] != STDIN_FILENO)
	{
		dup2(stock[0], STDIN_FILENO);
		close(stock[0]);
	}
	if (fd[1] != STDOUT_FILENO)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	if (fd[0] > 2)
		close(fd[0]);
}

static void	is_not_end(t_process *p, int stock[2], int fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		dup_pipe(fd, stock);
		pid = exec_pipe(p, stock[0], fd[1]);
	}
	else if (pid > 0)
	{
		if (fd[1] > 2)
			close(fd[1]);
		if (stock[0] != STDIN_FILENO)
			close(stock[0]);
		stock[0] = fd[0];
	}
	else
	{
		ft_dprintf(STDOUT_FILENO, "21sh: error fork\n");
		exit(1);
	}
}

static void	is_end(t_process *p, int stock[2], int fd[2])
{
	int		status;
	int		ret;
	pid_t	pid;

	ret = 0;
	pid = fork();
	if (pid == 0)
		exec_pipe(p, stock[0], STDOUT_FILENO);
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (fd[0] > 2)
			close(fd[0]);
		while ((pid = wait(&status)) > 0)
			;
	}
	else
	{
		ft_dprintf(STDOUT_FILENO, "21sh: error fork\n");
		exit(1);
	}
}

static void	act_p(t_process *p, int stock[2])
{
	int			fd[2];

	while (p->next)
	{
		if (pipe(fd) == -1)
			return ;
		if (check_is_exec(p->av[0], p->r) == 0)
		{
			stock[0] = fd[0];
			if (fd[1] > 2)
				close(fd[1]);
		}
		else
			is_not_end(p, stock, fd);
		p = p->next;
	}
	if (check_is_exec(p->av[0], p->r) == 0)
	{
		if (fd[0] > 2)
			close(fd[0]);
	}
	else
		is_end(p, stock, fd);
	if (stock[0] > 2)
		close(stock[0]);
}

void		act_p_prepare(t_process *p)
{
	int			stock[2];

	stock[0] = STDIN_FILENO;
	stock[1] = STDOUT_FILENO;
	sig_handler();
	act_p(p, stock);
	sig_ign();
}
