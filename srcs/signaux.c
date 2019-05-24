/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 10:54:15 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/24 03:50:41 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "job.h"

void		sighndler(int signum)
{
	(void)signum;
	ft_putchar('\n');
}

void		sig_z(int signum)
{
	t_shell	*shell;
	t_job	*j;
	//int	value = 0;

	j = get_first_job(NULL);
	shell = get_shell();
	tcsetpgrp(shell->term, j->pgid);
	// if (value)
	// {
	 	tcsetattr(shell->term, TCSADRAIN, &(j->tmodes));
	 	if (kill(-j->pgid, SIGCONT) < 0)
	 		ft_dprintf(j->r->error, "Kill not work!\n");
	// }
	wait_for_jobs(j);
	tcsetpgrp(shell->term, shell->pgid);
	tcgetattr(shell->term, &j->tmodes);
	tcsetattr(shell->term, TCSADRAIN, &(shell->term_shell));
}

void	ign_signaux(void)
{
	signal(SIGQUIT, sighndler);
	signal(SIGINT, sighndler);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGCHLD, SIG_IGN);
	signal(SIGCONT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGSTOP, SIG_IGN);
}

void	dfl_signaux(void)
{
	//signal(SIGINT, sighndler);
	//signal(SIGQUIT, sighndler);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
	signal(SIGCHLD, SIG_DFL);
	signal(SIGCONT, SIG_DFL);
	/*signal(SIGCONT, sig_z);
	signal(SIGTSTP, sig_z);
	signal(SIGSTOP, sig_z);*/
}