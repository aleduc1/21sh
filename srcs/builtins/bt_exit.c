/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 13:52:06 by apruvost          #+#    #+#             */
/*   Updated: 2019/05/16 15:28:39 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

/*
** exit [n]
**
** exit utility shall cause shell to exit from current execution env with exit
** status specified by unsigned decimal int n
** If current execution env is subshell env,
**    shell shall exit from subshell env with specified exit status and
** continue in env from which that subshell was invoked
** otherwise, shell utility shall terminate with specified exit status
** If n is specified, but its value is not etween 0 and 255 inclusively, the
** exit status is undefined
**
** A trap on EXIT shall be executed before shell terminates, except when exit
** utility invoked in trap itself, which case, shell exit immediately
**
** EXIT STATUS
**
** exit status shall be n, if specified, except thaht eaviour unspecified if
** not unsigned decimal int or greater than 255
** Otherwise, value shall be exit value of last command executed, or zero if no
** command executed
** When exit executed in trap action, last command is considered ti eb command
** that executed immediately preceding trap action
**
** RATIONALE
**
** certain exit status have een reserved for special uses and should be used by
** application only for those purposes :
** 126
**     A file to be executed was found, but it was not an executable utility
** 127
**     A utility to be executed was not found
** >128
**     A command was interrupted by a signal
**
** Behaviour of exit when given invalid argument or unknown option is
** unspecified, because of different practices in various historical implement
** A value larger than 255 might be truncated by shell, and be unavailable even
** to parent process taht uses waitid() to get full exit value
** It is recommanded thaht implementations that detect any usage error should
** cause a non-zero exit status
** (or if shell is interactive and error does not cause shell to abort, store
** non-zero value in "$?") but even this not done historicaly in all shells
*/

int		bt_exit(char **av, t_redirection *r)
{
	if (av == NULL || av[1] == NULL)
	{
		ft_dprintf(r->error, "exit\n");
		default_term_mode();
		get_env(1, NULL);
		exit(0);
	}
	if (ft_isstrnum(av[1]))
	{
		if (av[2] == NULL)
		{
			ft_dprintf(r->error, "exit\n");
			default_term_mode();
			get_env(1, NULL);
			exit(ft_atoi(av[1]));
		}
		ft_dprintf(r->error, "exit\n");
		ft_dprintf(r->error, "21sh: exit: too many arguments\n");
		return (1);
	}
	ft_dprintf(r->error, "exit\n");
	ft_dprintf(r->error, "21sh: exit: %s: numeric argument required\n", av[1]);
	default_term_mode();
	get_env(1, NULL);
	exit(255);
}
