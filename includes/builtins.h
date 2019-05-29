/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 16:01:05 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/28 10:15:01 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef BUILTINS_H
#	define BUILTINS_H

#include "env.h"
#include "job.h"

typedef struct		s_cd
{
	int		arg__;
	char	*directory;
	char	*curpath;
}					t_cd;

int					bt_exit(t_job *j);
int					bt_echo(char **av, t_redirection *r);

/*
** bt_jobs.c
*/

int					bt_jobs(char **av);
int					bt_bg(void);
int					bt_fg(void);
int					bt_export(char **value);

#	endif
