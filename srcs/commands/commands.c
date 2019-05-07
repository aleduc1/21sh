/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 10:50:50 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/07 21:04:55 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

/*
** simple command
*/

int		ft_simple_command(char **argv, t_token *token)
{
	t_redirection	*r;
	int				verif;

	parser_var(&argv);
	r = fill_redirection(token);
	if ((verif = is_builtin(argv, r)) == -1)
		verif = exec_fork(argv, r);
	close_file_command(token->command, &r);
	gest_return(verif);
	return (verif);
}

/*
** |
*/

int		choice_fd(int origin, int fd, int default_fd)
{
	if (origin == default_fd)
		return (fd);
	return (origin);
}

int		ft_pipe_b(char **argv, t_token *token, t_redirection *r)
{
	int	pipes[2];
	int	return_code;
	int	pids;

	pipe(pipes);
	r->out = choice_fd(r->out, pipes[1], STDOUT_FILENO);
	if ((pids = is_builtin(argv, r)) == -1)
		pids = add_process(argv, &return_code, r);
	close(pipes[1]);
	close_file_command(token->command, &r);
	return (pipes[0]);
}

int		ft_pipe(char **argv, t_token *token, int end_pipe)
{
	static int		in;
	int				return_code;
	int				pids;
	t_redirection	*r;

	parser_var(&argv);
	r = fill_redirection(token);
	r->in = choice_fd(r->in, in, STDIN_FILENO);
	if (end_pipe)
	{
		if ((return_code = is_builtin(argv, r)) == -1)
			pids = add_process(argv, &return_code, r);
		close_file_command(token->command, &r);
		gest_return(return_code);
	}
	else
		in = ft_pipe_b(argv, token, r);
	return (0);
}

/*
** ||
*/

int		ft_pipe_double(char **argv, t_token *token)
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

int		background_process(char **argv, t_token *token, int num_process)
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

int		ft_ampersand(char **argv, t_token *token, int num_process)
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

int		ft_ampersand_double(char **argv, t_token *token)
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
