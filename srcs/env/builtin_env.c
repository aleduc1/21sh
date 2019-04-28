/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 17:36:44 by sbelondr          #+#    #+#             */
/*   Updated: 2019/04/28 11:47:53 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/env.h"

int		builtin_env(t_env **my_env, t_cmd *cmd)
{
	int		i;
	char	**lst_env;

	lst_env = create_list_env(*my_env, 1);
	i = -1;
	while (lst_env[++i])
		ft_dprintf(cmd->out->fd, "%s\n", lst_env[i]);
	ft_arraydel(&lst_env);
	return (0);
}

int		builtin_set(t_env **my_env, t_cmd *cmd)
{
	int		i;
	char	**lst_env;

	lst_env = create_list_env(*my_env, 0);
	i = -1;
	while (lst_env[++i])
		ft_dprintf(cmd->out->fd, "%s\n", lst_env[i]);
	ft_arraydel(&lst_env);
	return (0);
}
