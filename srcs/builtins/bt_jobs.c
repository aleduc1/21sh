/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_jobs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 10:54:45 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/28 12:56:32 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job.h"

char		*ft_inter_signal(int sig)
{
	;
}

static void	bt_jobs_p(t_job *j, int is_stopped)
{
	if (is_stopped)
		ft_printf("%d\n", j->first_process->pid);
	else
		ft_printf("%d\n", j->first_process->pid);
}

static void	bt_jobs_l(t_job *j, int is_stopped)
{
	if (is_stopped)
		ft_printf("[%d]%c\t%d: %d\t%s\n", j->first_process->process_id,
			'+', j->first_process->pid, 11, j->first_process->cmd[0]);
	else
	{
		ft_printf("[%d]%c\t%d: %d\t%s\n", j->first_process->process_id,
			'-', j->first_process->pid, 11, j->first_process->cmd[0]);
	}
}

static void	bt_jobs_s(t_job *j, int is_stopped)
{
	if (is_stopped)
		ft_printf("[%d]%c\tStopped(SIGTSTP)\t%s\n", j->first_process->process_id,
			'+', j->first_process->cmd[0]);
	else
		ft_printf("[%d]%c\tCompleted()\t%s\n", j->first_process->process_id,
			'-', j->first_process->cmd[0]);
	ft_printf("signal: %d - %d", WSTOPSIG(j->first_process->status),
	WTERMSIG(j->first_process->status));
}

int		bt_jobs(char **av)
{
	t_job	*j;
	void	(*p)(t_job*, int);

	update_status();
	p = &bt_jobs_s;
	while (*(++av))
	{
		if (ft_strequ(*av, "-p"))
			p = &bt_jobs_p;
		else if (ft_strequ(*av, "-l"))
			p = &bt_jobs_l;
	}
	j = get_first_job(NULL);
	while (j)
	{
		if (job_is_completed(j))
			(*p)(j, 0);
		else if (job_is_stop(j) && (!j->notified))
			(*p)(j, 1);
		j = j->next;
	}
	return (0);
}

int		bt_bg(void)
{
	t_job	*j;
	t_job	*is_stopped;

	j = get_first_job(NULL);
	is_stopped = NULL;
	while (j)
	{
		if (j->first_process->stopped == 1)
			is_stopped = j;
		j = j->next;
	}
	if (!is_stopped)
	{
		ft_dprintf(2, "42sh: bg no current job\n");
		return (-2);
	}
	continue_job(is_stopped, 0);
	return (0);
}

int		bt_fg(void)
{
	t_job	*j;
	t_job	*is_stopped;

	j = get_first_job(NULL);
	is_stopped = NULL;
	while (j)
	{
		if (j->first_process->stopped == 1)
			is_stopped = j;
		j = j->next;
	}
	if (!is_stopped)
	{
		ft_dprintf(2, "42sh: fg: no current job\n");
		return (-2);
	}
	continue_job(is_stopped, 1);
	return (0);
}
