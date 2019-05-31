/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gest_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 11:34:26 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/24 16:39:09 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job.h"

/*
** https://www.gnu.org/software/libc/manual/html_node/Stopped-and-Terminated-Jobs.html#Stopped-and-Terminated-Jobs
*/

/*
** stock le status du pid
** WIFSIGNALED -> check if process exist
** WIFSTOPPED -> True if the process has
** not terminated, but has stopped and can be restarted.
*/

int		mark_process_status(pid_t pid, int status)
{
	t_job		*j;
	t_process	*p;

	if (pid > 0)
	{
		j = get_first_job(NULL);
		while (j)
		{
			p = j->first_process;
			while (p)
			{
				if (pid == p->pid)
				{
					p->status = status;
					if (WIFSTOPPED(status))
						p->stopped = 1;
					else
					{
						p->completed = 1;
						if (WIFSIGNALED(status))
							ft_dprintf(j->r->error, "Process end pid = %d %d",
							(int)pid, status);
					}
					return (0);
				}
				p = p->next;
			}
			j = j->next;
		}
	}
	return (-1);
}

void	update_status(void)
{
	int		status;
	pid_t	pid;

	dfl_signaux();
	while (1)
	{
		pid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG);
		if (mark_process_status(pid, status))
			break ;
	}
	ign_signaux();
}

void	wait_for_jobs(t_job *j)
{
	int		status;
	pid_t	pid;

	dfl_signaux();
	while (1)
	{
		pid = waitpid(-j->pgid, &status, WUNTRACED);
		if (mark_process_status(pid, status) || job_is_stop(j) ||
			job_is_completed(j))
			break ;
	}
	ign_signaux();
}

void	job_info(t_job *j, char *status)
{
	ft_dprintf(j->r->error, "%s [%d]: %s\n", j->first_process->cmd[0],
		(int)j->pgid, status);
}

void	job_notif(void)
{
	t_job	*j;
	t_job	*last;
	t_job	*next;

	update_status();
	j = get_first_job(NULL);
	last = NULL;
	while (j)
	{
		next = j->next;
		if (job_is_completed(j))
		{
			job_info(j, "completed");
			(last) ? last->next = next : get_first_job(next);
			free_job(&j);
		}
		else if (job_is_stop(j) && !j->notified)
		{
			job_info(j, "stopped");
			j->notified = 1;
			last = j;
		}
		else
			last = j;
		j = next;
	}
}

void	job_running(t_job *j)
{
	t_process	*p;

	p = j->first_process;
	while (p)
	{
		p->stopped = 0;
		p = p->next;
	}
	j->notified = 0;
}

void	continue_job(t_job *j, int fg)
{
	job_running(j);
	if (fg)
		add_in_fg(j, 1);
	else
		add_in_bg(j, 1);
}
