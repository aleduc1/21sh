/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 17:36:44 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/07 00:10:13 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int		builtin_env(t_redirection *r)
{
	int		i;
	char	**lst_env;

	i = -1;
	lst_env = create_list_env(get_env(0), 1);
	while (lst_env[++i])
		ft_dprintf(r->out, "%s\n", lst_env[i]);
	if (i == 0)
		ft_dprintf(r->error, "You are nothing value in env\n");
	ft_arraydel(&lst_env);
	return (0);
}

int		builtin_set(t_redirection *r)
{
	int		i;
	char	**lst_env;

	lst_env = create_list_env(get_env(0), 0);
	i = -1;
	while (lst_env[++i])
		ft_dprintf(r->out, "%s\n", lst_env[i]);
	if (i == 0)
		ft_dprintf(r->error, "You are nothing value in env\n");
	ft_arraydel(&lst_env);
	return (0);
}
