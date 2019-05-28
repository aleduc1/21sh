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

void	redirection_fd_pipe(t_redirection *r)
{
	if (r->fd_pipe >= 0)
		close(r->fd_pipe);
	if (r->in != STDIN_FILENO)
	{
		dup2(r->in, STDIN_FILENO);
		close(r->in);
	}
	if (r->out != STDOUT_FILENO)
	{
		dup2(r->out, STDOUT_FILENO);
		close(r->out);
	}
	if (r->error != STDERR_FILENO)
	{
		dup2(r->error, STDERR_FILENO);
		close(r->error);
	}
}

static int	is_not_end(t_job *j, t_process *p, int in)
{
	int		fd[2];
	int		pid;

	pipe(fd);
	if (j->r->out == STDOUT_FILENO)
		j->r->out = fd[1];
	if (j->r->in == STDIN_FILENO)
		j->r->in = in;
	j->r->fd_pipe = fd[0];
	pid = fork();
	if (pid == 0)
	{
		if ((pid = is_builtin(p->cmd, j->r)) == -1)
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
	if ((verif = is_builtin(p->cmd, j->r)) == -1)
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
	static int		in;
	t_job			*j;
	t_process		*p;

	j = edit_lst_job(argv, t, NULL);
	p = j->first_process;
	if (end_pipe == 0)
		in = is_not_end(j, p, in);
	else
	{
		in = is_end(j, p, in);
		wait_for_jobs(j);
		gest_return(in);
		in = 0;
	}
	if (p->completed == 1 || p->pid == 0)
	{
		close_file_command(t->command, &j->r);
		clean_fuck_list();
	}
	return (0);
}
