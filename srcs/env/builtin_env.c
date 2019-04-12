/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 17:36:44 by sbelondr          #+#    #+#             */
/*   Updated: 2019/04/12 11:18:42 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "env.h"
#include "../../includes/env.h"

int		builtin_env(t_env **my_env, int fd_stock[3])
{
	int		i;
//	int		fd;
	char	**lst_env;

(void)fd_stock;	
	lst_env = create_list_env(*my_env, 1);
/*	if (fd_stock[0] != 0)
		dup2(fd_stock[0], 0);
	if (fd_stock[1] != 1)
		dup2(fd_stock[1], 1);
	if (fd_stock[2] != 2)
		dup2(fd_stock[2], 2);
//	fd = dest_output(&(*my_env));
*/	i = -1;
	while (lst_env[++i])
		ft_dprintf(fd_stock[1], "%s\n", lst_env[i]);
//	if (fd > 2)
//		close(fd);
	ft_arraydel(&lst_env);
	close_file(&(*my_env));
	return (0);
}

int		builtin_set(t_env **my_env, int fd_stock[3])
{
	int		i;
//	int		fd;
	char	**lst_env;

	lst_env = create_list_env(*my_env, 0);
//	if (fd_stock[0] != 0)
	//	dup2(fd_stock[0], 0);
	//ft_printf("coucou %d\n", fd_stock[1]);
//	if (fd_stock[1] != 1)
//		dup2(fd_stock[1], 1);
//	ft_printf("coucou %d\n", fd_stock[1]);
//	if (fd_stock[2] != 2)
//		dup2(fd_stock[2], 2);
//	ft_printf("coucou\n");
//	fd = dest_output(&(*my_env));
	i = -1;
	while (lst_env[++i])
		ft_dprintf(fd_stock[1], "%s\n", lst_env[i]);
//	if (fd > 2)
//		close(fd);
	ft_arraydel(&lst_env);
	close_file(&(*my_env));
	return (0);
}
