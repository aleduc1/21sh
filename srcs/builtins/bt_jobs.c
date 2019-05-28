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

int		bt_jobs(void)
{
	t_job	*j;

	update_status();
	j = get_first_job(NULL);
	while (j)
	{
		if (job_is_completed(j))
			job_info(j, "completed");
		else if (job_is_stop(j) && (!j->notified))
			job_info(j, "stopped");
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
