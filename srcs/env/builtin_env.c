/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 17:36:44 by sbelondr          #+#    #+#             */
/*   Updated: 2019/04/15 12:45:36 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "env.h"
#include "../../includes/env.h"

int		builtin_env(t_env **my_env, int fd_stock[3])
{
	int		i;
	char	**lst_env;

	lst_env = create_list_env(*my_env, 1);
	i = -1;
	while (lst_env[++i])
		ft_dprintf(fd_stock[1], "%s\n", lst_env[i]);
	ft_arraydel(&lst_env);
	return (0);
}

int		builtin_set(t_env **my_env, int fd_stock[3])
{
	int		i;
	char	**lst_env;

	lst_env = create_list_env(*my_env, 0);
	i = -1;
	while (lst_env[++i])
		ft_dprintf(fd_stock[1], "%s\n", lst_env[i]);
	ft_arraydel(&lst_env);
	return (0);
}
