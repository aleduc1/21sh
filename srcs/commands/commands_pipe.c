/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 10:50:50 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/28 11:50:48 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "job.h"

static int	is_not_end(t_job *j, t_process *p, int in)
{
	int		fd[2];
	int		pid;

	pipe(fd);
	if (j->r->in == STDIN_FILENO)
		j->r->in = in;
	j->r->fd_pipe = fd[0];
	pid = fork();
	if (pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		if (j->r->out == STDOUT_FILENO)
			j->r->out = fd[1];
		if ((pid = is_builtin(j, NULL)) == -1)
		{
			if (is_in_path(&p->cmd) == 1)
				pid = launch_job(j, 1);
			else
				display_error_command(j->r, p->cmd);
		}
		execve("/bin/test", NULL, NULL);
	}
	if (in != 0)
		close(in);
	close(fd[1]);
	return (fd[0]);
}

static int	is_end(t_job *j, t_process *p, int in)
{
	int	verif;

	dfl_signaux();
	if (j->r->in == STDIN_FILENO)
		j->r->in = in;
	j->r->fd_pipe = -1;
	if ((verif = is_builtin(j, NULL)) == -1)
	{
		if (is_in_path(&p->cmd) == 1)
			verif = launch_job(j, 1);
		else
			display_error_command(j->r, p->cmd);
	}
	close(in);
	return (verif);
}

int			ft_pipe(char **argv, t_token *t, int end_pipe)
{
	int		in;
	t_job	*j;

	if (end_pipe == 0)
		create_new_job(argv, t);
	if (end_pipe > 0)
		add_process(argv, t);
	if (end_pipe == 2)
	{
		j = get_end_job();
		launch_job_pipe(j, 1);
	}
	return (0);
}
