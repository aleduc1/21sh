/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 10:50:50 by sbelondr          #+#    #+#             */
/*   Updated: 2019/04/12 17:10:47 by sbelondr         ###   ########.fr       */
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
		fd_stock[1] = pipes[1];//dest_output(&(*my_env));
		if ((pids[i] = is_builtin(commands[i], &(*my_env), fd_stock)) == -1)
			pids[i] = add_process(commands[i], fd_stock, *my_env, &return_code);
		close(pipes[1]);
		//close_file(&(*my_env));
		fd_stock[0] = pipes[0];
	}
	fd_stock[1] = dest_output(&(*my_env));
	if ((pids[i] = is_builtin(commands[i], &(*my_env), fd_stock)) == -1)
		pids[i] = add_process(commands[i], fd_stock, *my_env, &return_code);
	close(fd_stock[0]);
	close_file(&(*my_env));
	close_error_file(&(*my_env));
	return (return_code);
}

int		choice_fd(int fd_base, int fd, int origin)
{
	int	stock_fd;

	if (origin == fd_base)
		stock_fd = fd;
	else
		stock_fd = fd_base;
	return (stock_fd);
}

int		ft_multiple_pipe_ts(t_commands *cmds, int nb, t_env **my_env)
{
	int	i;
	int	return_code;
	int	pids[nb];
	int	pipes[2];
	int	fd_stock[3];

	i = -1;
	fd_stock[0] = 0;
	fd_stock[2] = cmds->fd_stock[2];
	while (++i < (nb - 1))
	{
		pipe(pipes);
		fd_stock[1] = choice_fd(cmds->fd_stock[1], pipes[1], 1);
		if ((pids[i] = is_builtin(cmds->command, &(*my_env), fd_stock)) == -1)
			pids[i] = add_process(cmds->command, fd_stock, *my_env, &return_code);
		close(pipes[1]);
//		close(fd_stock[1]);
		cmds = cmds->next;
		fd_stock[0] = pipes[0];
	}
	ft_printf("cmds->command = %s|\n", cmds->command);
	fd_stock[1] = dest_output(&(*my_env));
	if ((pids[i] = is_builtin(cmds->command, &(*my_env), fd_stock)) == -1)
		pids[i] = add_process(cmds->command, fd_stock, *my_env, &return_code);
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
	fd_stock[1] = dest_output(&(*my_env));
	fd_stock[2] = dest_error_output(&(*my_env));
	parser_var(&command, *my_env);
	if (is_builtin(command, &(*my_env), fd_stock) != -1)
		verif = 0;
	else
		verif = exec_fork(command, &(*my_env), fd_stock);
	close_file(&(*my_env));
	close_error_file(&(*my_env));
	return (verif);
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
	if ((!lst) || (!(*lst)))
		return ;
	while ((*lst)[++i])
		ft_arraydel(&((*lst)[i]));
	free(*lst);
	(*lst) = NULL;
}

t_commands	*init_commands(char **commands, int fd_stock[3])
{
	t_commands	*cmds;

	if (!(cmds = (t_commands*)malloc(sizeof(t_commands) * 1)))
		return (NULL);
	cmds->command = ft_arraydup(commands);
	cmds->fd_stock[0] = fd_stock[0];
	cmds->fd_stock[1] = fd_stock[1];
	cmds->fd_stock[2] = fd_stock[2];
	cmds->next = NULL;
	return (cmds);
}

void	delete_commands(t_commands **cmds)
{
	t_commands	*tmp;

	while (*cmds)
	{
		tmp = *cmds;
		*cmds = (*cmds)->next;
		ft_arraydel(&(tmp->command));
		free(tmp);
		tmp = NULL;
	}
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

	int		fd_stock[3];

	fd_stock[0] = 0;
	fd_stock[1] = 1;
	fd_stock[2] = 2;

	if (ac == -1)
		return (0);
	env = init_env();
	test = ft_arraydup(testa);
	test_b = ft_arraydup(testb);
	command = ft_arraydup(av + 1);

	t_commands	*cmds;
	t_commands	*tmp;
	
	cmds = init_commands(command, fd_stock);
	cmds->fd_stock[1] = dest_output(&env);
//	cmds->next = init_commands(test, fd_stock);
	tmp = init_commands(test_b, fd_stock);
	cmds->next = tmp;
	i = ft_multiple_pipe_ts(cmds, 3, &env);
	delete_commands(&cmds);

//	i = ft_simple_command(command, &env);
//	ft_printf("i = %d\n", i);
	mlt_commands = ft_arrays_dim(2, command, test_b);
//	i = ft_multiple_pipe(mlt_commands, 2, &env);
//	ft_printf("i = %d\n", i);
//	i = ft_pipe_double(command, test, &env);
//	ft_printf("i = %d\n", i);
//	i = ft_ampersand_double(command, test, &env);
//	ft_printf("i = %d\n", i);
	gest_return(i, &env);
	free_env(&env);
	ft_arraydel(&command);
	ft_arraydel(&test);
	ft_arraydel(&test_b);
	ft_arrays_dim_del(&mlt_commands);
	return (0);
}


