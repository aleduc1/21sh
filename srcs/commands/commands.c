/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 10:50:50 by sbelondr          #+#    #+#             */
/*   Updated: 2019/06/19 18:05:42 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

/*
** simple command
*/

int			ft_simple_command(char **argv, t_token *token)
{
	t_redirection	*r;
	int				verif;
	char			**cpy_argv;

	if (!argv[0])
		return (-1);
	cpy_argv = ft_arraydup(argv);
	parser_var(&cpy_argv);
	if (check_last_command() == -5)
	{
		ft_arraydel(&cpy_argv);
		gest_return(1);
		return (-1);
	}
	r = fill_redirection(token);
	if ((verif = is_builtin(cpy_argv, r)) == -1)
		verif = exec_fork(cpy_argv, r);
	close_file_command(token->command, &r);
	if (!(verif == 2 && check_last_command() == 130))
		gest_return(verif);
	ft_arraydel(&cpy_argv);
	return (verif);
}

/*
** ||
*/

int			ft_pipe_double(char **argv, t_token *token)
{
	int		check;
	char	*str;

	str = value_line_path("?", 0);
	check = ft_atoi(str);
	if (check == -1)
		check = ft_simple_command(argv, token);
	ft_strdel(&str);
	return (check);
}

/*
** &
** num_process: processus en cours (mettre a 1 la premiere fois)
*/

static int	background_process(char **argv, t_token *token, int num_process)
{
	int	result;
	int	pid;

	pid = fork();
	if (pid > 0)
		ft_printf("[%d] %d\n", num_process, pid);
	waitpid(pid, &result, 0);
	if (pid == 0)
	{
		ft_simple_command(argv, token);
		execve("/bin/test", NULL, NULL);
		exit(pid);
	}
	return (pid);
}

int			ft_ampersand(char **argv, t_token *token, int num_process)
{
	int	result;

	result = 0;
	signal(SIGTTOU, NULL);
	result = background_process(argv, token, num_process);
	if (result != -1)
	{
		ft_printf("[%d] Done\t%s\n", num_process, argv[0]);
		kill(result, SIGTTOU);
	}
	return (result);
}

/*
** &&
*/

int			ft_ampersand_double(char **argv, t_token *token)
{
	int		check;
	char	*str;

	str = value_line_path("?", 0);
	check = ft_atoi(str);
	if (check != -1)
		check = ft_simple_command(argv, token);
	ft_strdel(&str);
	return (check);
}
