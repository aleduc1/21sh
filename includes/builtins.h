/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 16:01:05 by sbelondr          #+#    #+#             */
/*   Updated: 2019/06/02 17:36:03 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef BUILTINS_H
#	define BUILTINS_H

#include "env.h"
#include <sys/param.h>

int					bt_exit(char **av, t_redirection *r);
int					bt_echo(char **av, t_redirection *r);
int					builtin_env_display(t_redirection *r);

#	endif
