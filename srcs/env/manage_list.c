/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 10:50:50 by sbelondr          #+#    #+#             */
/*   Updated: 2019/04/11 18:55:54 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "env.h"
#include "../../includes/env.h"
/*
** &
*/

int		ft_ampersand(char **f_command, char **s_command, t_env **my_env)
{
	(void)f_command;
	(void)s_command;
	(void)my_env;
	return (0);
}

/*
** &&
*/

int		ft_ampersand_double(char **f_command, char **s_command, t_env **my_env)
{
	int	check;

	check = ft_simple_command(f_command, &(*my_env));
	if (check != -1 && check != 256)
		check = ft_simple_command(s_command, &(*my_env));
	return (check);
}

/*
** |
*/

int		ft_pipe(char **f_command, char **s_command, t_env **my_env)
{
	int		return_code;
	int		pids[2];
	int		pipes[2];
	int		fd_stock[3];

	pipe(pipes);
	fd_stock[0] = 0;
	fd_stock[1] = pipes[1];
	fd_stock[2] = dest_error_output(&(*my_env));
	if ((pids[0] = is_builtin(f_command, &(*my_env), fd_stock)) == -1)
		pids[0] = add_process(f_command, fd_stock, *my_env, &return_code);
	close(pipes[1]);
	fd_stock[0] = pipes[0];
	fd_stock[1] = dest_output(&(*my_env));
	if ((pids[1] = is_builtin(s_command, &(*my_env), fd_stock)) == -1)
		pids[1] = add_process(s_command, fd_stock, *my_env, &return_code);
	close(fd_stock[0]);
	close_file(&(*my_env));
	close_error_file(&(*my_env));
	return (return_code);
}

/*
** ||
*/

int		ft_pipe_double(char **f_command, char **s_command, t_env **my_env)
{
	int	check;

	check = ft_simple_command(f_command, &(*my_env));
	if (check == -1 || check == 256)
		check = ft_simple_command(s_command, &(*my_env));
	return (check);
}

/*
** simple
*/

int		ft_simple_command(char **command, t_env **my_env)
{
	int		fd_stock[3];
	int		verif;

	fd_stock[0] = 0;
	fd_stock[1] = 1;
	fd_stock[2] = 2;
	parser_var(&command, *my_env);
	if (is_builtin(command, &(*my_env), fd_stock) != -1)
		verif = 0;
	else
		verif = exec_fork(command, &(*my_env));
	return (verif);
}

int		main(int ac, char **av)
{
	char	**command;
	t_env	*env;

	if (ac == -1)
		return (0);
	env = init_env();
	command = ft_arraydup(av + 1);
	int	i = ft_simple_command(command, &env);
	free_env(&env);
	ft_arraydel(&command);
	ft_printf("i = %d\n", i);
	return (0);
}


