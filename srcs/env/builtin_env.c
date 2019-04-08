/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 17:36:44 by sbelondr          #+#    #+#             */
/*   Updated: 2019/04/08 11:11:10 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void		builtin_env(t_env **my_env)
{
	int		i;
	int		fd;
	char	**lst_env;

	lst_env = create_list_env(*my_env, 1);
	fd = dest_output(&(*my_env));
	i = -1;
	while (lst_env[++i])
		ft_dprintf(fd, "%s\n", lst_env[i]);
	if (fd > 2)
		close(fd);
	ft_arraydel(&lst_env);
	close_file(&(*my_env));
}

void		builtin_set(t_env **my_env)
{
	int		i;
	int		fd;
	char	**lst_env;

	lst_env = create_list_env(*my_env, 0);
	fd = dest_output(&(*my_env));
	i = -1;
	while (lst_env[++i])
		ft_dprintf(fd, "%s\n", lst_env[i]);
	if (fd > 2)
		close(fd);
	ft_arraydel(&lst_env);
	close_file(&(*my_env));
}
