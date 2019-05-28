/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_jobs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 10:54:45 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/28 09:16:10 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job.h"

int		bt_jobs(void)
{
	t_job	*j;

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

	j = get_first_job(NULL);
	if (j->first_process->stopped == 0)
	{
		ft_dprintf(2, "42sh: bg no current job\n");
		return (-2);
	}
	continue_job(j, 0);
	return (0);
}

int		bt_fg(void)
{
	t_job	*j;

	j = get_first_job(NULL);
	if (j->first_process->stopped == 0)
	{
		ft_dprintf(2, "42sh: fg: no current job\n");
		return (-2);
	}
	continue_job(j, 1);
	return (0);
}
