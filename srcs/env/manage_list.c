/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 10:50:50 by sbelondr          #+#    #+#             */
/*   Updated: 2019/04/12 11:00:13 by sbelondr         ###   ########.fr       */
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

int		ft_multiple_pipe(char ***commands, int nb, t_env **my_env)
{
	int	i;
	int	return_code;
	int	pids[nb];
	int	pipes[2];
	int	fd_stock[3];

	i = -1;
	fd_stock[0] = 0;
	fd_stock[2] = dest_error_output(&(*my_env));
	while (++i < (nb - 1))
	{
		pipe(pipes);
		fd_stock[1] = pipes[1];
		if ((pids[i] = is_builtin(commands[i], &(*my_env), fd_stock)) == -1)
			pids[i] = add_process(commands[i], fd_stock, *my_env, &return_code);
		close(pipes[1]);
		fd_stock[0] = pipes[0];
	}
	fd_stock[0] = pipes[0];
	fd_stock[1] = dest_output(&(*my_env));
	if ((pids[i] = is_builtin(commands[i], &(*my_env), fd_stock)) == -1)
		pids[i] = add_process(commands[i], fd_stock, *my_env, &return_code);
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

char	***create_arrays_commands(char **f, char **s, char **t)
{
	char	***final;

	if (!(final = (char***)malloc(sizeof(char**) * 4)))
		return (NULL);
	final[0] = ft_arraydup(f);
	final[1] = ft_arraydup(s);
	final[2] = ft_arraydup(t);
	final[3] = NULL;
	return (final);
}

char	***ft_arrays_dim(int n, ...)
{
	int		i;
	va_list	ap;
	char	**data;
	char	***final;

	va_start(ap, n);
	if (!(final = (char***)malloc(sizeof(char**) * (n + 1))))
		return (NULL);
	i = -1;
	while (++i < n)
	{
		data = va_arg(ap, char**);
		final[i] = ft_arraydup(data);
	}
	final[i] = NULL;
	va_end(ap);
	return (final);
}

void	ft_arrays_dim_del(char ****lst)
{
	int	i;

	i = -1;
	while ((*lst)[++i])
		ft_arraydel(&((*lst)[i]));
	free(*lst);
	(*lst) = NULL;
}

int		main(int ac, char **av)
{
	char	***mlt_commands;
	char	**command;
	char	**test;
	char	*testa[3] = {"cat", "-e", NULL};
	char	**test_b;
	char	*testb[2] = {"wc", NULL};
	t_env	*env;
	int		i;

	if (ac == -1)
		return (0);
	env = init_env();
	test = ft_arraydup(testa);
	test_b = ft_arraydup(testb);
	command = ft_arraydup(av + 1);
//	i = ft_simple_command(command, &env);
//	gest_return(i, &env);
//	ft_printf("i = %d\n", i);
//	i = ft_pipe(command, test, &env);
//	ft_printf("i = %d\n", i);
//	char	***multiple_commands = create_arrays_commands(command, test, test_b);
	mlt_commands = ft_arrays_dim(3, command, test, test_b);
	i = ft_multiple_pipe(mlt_commands, 3, &env);
	ft_printf("i = %d\n", i);
//	i = ft_pipe_double(command, test, &env);
//	ft_printf("i = %d\n", i);
//	i = ft_ampersand_double(command, test, &env);
//	ft_printf("i = %d\n", i);
	free_env(&env);
	ft_arraydel(&command);
	ft_arraydel(&test);
	ft_arraydel(&test_b);
	ft_arrays_dim_del(&mlt_commands);
	return (0);
}


