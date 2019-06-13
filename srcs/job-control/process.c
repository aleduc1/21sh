/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 09:42:05 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/28 11:28:20 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job.h"

int		launch_process(t_process *p, pid_t pgid, t_redirection *r, int fg)
{
	pid_t	pid;
	char	**environ;
	t_shell	*s;

	s = get_shell();
	dfl_signaux();
	environ = create_list_env(get_env(0, NULL), 0);
	if (s->interactive)
	{
		pid = getpid();
		if (pgid == 0)
			pgid = pid;
		setpgid(pid, pgid);
		if (fg)
			tcsetpgrp(s->term, pgid);
	}
	redirection_fd(r);
	execve(p->cmd[0], p->cmd, environ);
	ft_dprintf(r->error, "21sh: command not found: %s\n", p->cmd[0]);
	execve("/bin/test", NULL, NULL);
	exit(0);
}

void	act_job(t_job *j, int fg)
{
	t_shell	*shell;

	shell = get_shell();
	if (!shell->interactive)
		wait_for_jobs(j);
	else if (fg)
		add_in_fg(j, 0);
	else
	{
		job_info(j, "launched");
		add_in_bg(j, 0);
	}
}

int			launch_job(t_job *j, int fg)
{
	t_process	*p;
	pid_t		pid;

	p = j->first_process;
	while (p)
	{
		pid = fork();
		if (pid == 0)
			launch_process(p, j->pgid, j->r, fg);
		else if (pid < 0)
			ft_dprintf(j->r->error, "Error fork\n");
		else
		{
			p->pid = pid;
			if (get_shell()->interactive)
			{
				if (!(j->pgid))
					j->pgid = pid;
				setpgid(pid, j->pgid);
			}
		}
		p = p->next;
	}
	act_job(j, fg);
	return (0);
}

int			launch_job_pipe(t_job *j, int fg)
{
	int			fd[2];
	t_process	*p;
	pid_t		pid;
	int			in;
	int			verif;

	in = 0;
	p = j->first_process;
	display_lst_job(j);
	while (p)
	{
		dfl_signaux();
		if (p->next)
		{
			ft_printf("cmd = %s\n", p->cmd[0]);
			pipe(fd);
			if (j->r->out == STDOUT_FILENO)
				j->r->out = fd[1];
			j->r->fd_pipe = fd[0];
			in = fd[0];
		}
		else
		{
			j->r->fd_pipe = -1;
		}
	//	if (j->r->in == STDIN_FILENO)
				j->r->in = in;
		pid = fork();
		if (pid == 0)
		{
			//dup2(j->r->out, STDOUT_FILENO);
			if ((verif = is_builtin(j, NULL)) == -1)
			{
				if (is_in_path(&p->cmd) == 1)
				{
					ft_printf("ici %s\n", p->cmd[0]);
					verif = launch_process(p, j->pgid, j->r, fg);
				}
				else
					display_error_command(j->r, p->cmd);
			}
			execve("/bin/test", NULL, NULL);
		}
		else
		{
			p->pid = pid;
			if (get_shell()->interactive)
			{
				if (!(j->pgid))
					j->pgid = pid;
				setpgid(pid, j->pgid);
			}
		}
		ign_signaux();
		if (in != 0)
			close(in);
		close(fd[1]);
		p = p->next;
	}
	act_job(j, fg);
	return (0);
}