/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_jobs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 10:54:45 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/24 02:08:10 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job.h"

int		bt_jobs(t_redirection *r)
{
	job_notif();
	return (0);
}

int		bt_bg(t_redirection *r)
{
	t_job	*j;

	j = get_first_job(NULL);
	continue_job(j, 0);
	return (0);
}

int		bt_fg(t_redirection *r)
{
	t_job	*j;

	j = get_first_job(NULL);
	continue_job(j, 1);
	return (0);
}
