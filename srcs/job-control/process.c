/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 09:42:05 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/23 15:28:13 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job.h"

static int	launch_process(t_process *p, pid_t pgid, t_redirection *r, int fg)
{
	pid_t	pid;
	char	**environ;
	t_shell	*s;

	s = get_shell();
	environ = create_list_env(get_env(0, NULL), 0);
	dfl_signaux();
	if (s->interactive)
	{
		pid = getpid();
		if (pgid == 0)
			pgid = pid;
		setpgid(pid, pgid);
		if (fg)
			tcsetpgrp(s->term, pgid);
	}
	redirection_fd_pipe(r);
	execve(p->cmd[0], p->cmd, environ);
	ft_dprintf(r->error, "21sh: command not found: %s\n", p->cmd[0]);
	execve("/bin/test", NULL, NULL);
	exit(0);
}

static void	act_job(t_job *j, int fg)
{
	job_info(j, "launched");
	if (!get_shell()->interactive)
		wait_for_jobs(j);
	else if (fg)
		add_in_fg(j, 0);
	else
		add_in_bg(j, 0);
	ign_signaux();
}

int			launch_job(t_job *j, int fg)
{
	t_process	*p;
	pid_t		pid;

	p = j->first_process;
	while (p)
	{
		pid = fork();
		job_notif();
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
