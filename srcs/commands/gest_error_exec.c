/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gest_error_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 08:43:53 by sbelondr          #+#    #+#             */
/*   Updated: 2019/07/09 13:35:11 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

int		gest_error_path(char *cmd, t_redirection *r)
{
	if (check_last_command() == -6)
	{
		ft_dprintf(r->error, "21sh: %s: Permission denied\n", cmd);
		return (126);
	}
	ft_dprintf(r->error, "21sh: command not found: %s\n", cmd);
	return (127);
}

void	gest_error_exec(char *cmd, t_redirection *r)
{
	if ((!cmd) || ft_strequ(cmd, ""))
		ft_dprintf(r->error, "21sh: command not found: %s\n", cmd);
	else
		ft_dprintf(r->error, "21sh: is a directory: %s\n", cmd);
}
