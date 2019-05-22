/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_job.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 09:24:08 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/22 09:40:58 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job.h"

t_process	*init_process(void)
{
	t_process	*p;

	if (!(p = (t_process*)malloc(sizeof(t_process) * 1)))
		return (NULL);
	p->cmd = NULL;
	p->pid = 0;
	p->completed = 0;
	p->stopped = 0;
	p->status = 0;
	p->next = NULL;
	return (p);
}

t_job		*init_job(void)
{
	t_job	*j;

	if (!(j = (t_job*)malloc(sizeof(t_job) * 1)))
		return (NULL);
	j->first_process = init_process();
	j->pgid = 0;
	j->notified = 0;
	j->r = NULL;
	j->next = NULL;
	return (j);
}

void		free_job(t_job *j)
{
	free(j);
	j = NULL;
}

t_job	*get_first_job(t_job *new_job)
{
	static t_job	*job;

	if (!job)
		job = init_job();
	if (new_job)
		job = new_job;
	return (job);
}

t_job	*find_job(pid_t pid)
{
	t_job	*job;

	job = get_first_job(NULL);
	while (job)
	{
		if (job->pgid == pid)
			return (job);
		job = job->next;
	}
	return (NULL);
}

int		job_is_stop(t_job *job)
{
	t_process	*p;

	p = job->first_process;
	while (p)
	{
		if ((!p->completed) && (!p->stopped))
			return (0);
		p = p->next;
	}
	return (1);
}

int		job_is_completed(t_job *job)
{
	t_process	*p;

	p = job->first_process;
	while (p)
	{
		if (!p->completed)
			return (0);
		p = p->next;
	}
	return (1);
}
