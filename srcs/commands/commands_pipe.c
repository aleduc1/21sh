/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 10:50:50 by sbelondr          #+#    #+#             */
/*   Updated: 2019/06/02 18:20:30 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

static int	exec_is_not_end(char **argv, int fd[2], t_redirection *r, int pid)
{
	dup2(fd[1], STDOUT_FILENO);
	if (r->out == STDOUT_FILENO)
		r->out = fd[1];
	if ((pid = is_builtin(argv, r)) == -1)
		pid = add_pipe_process(argv, r);
	execve("/bin/test", NULL, NULL);
	return (pid);
}

static int	is_not_end(char **argv, int in, t_redirection *r)
{
	int		fd[2];
	pid_t	pid;

	sig_handler();
	pipe(fd);
	if (r->in == STDIN_FILENO)
		r->in = in;
	r->fd_pipe = fd[0];
	if (check_is_exec(argv[0], r) == 0)
	{
		sig_ign();
		if (in != 0)
			close(in);
		close(fd[1]);
		return (fd[0]);
	}
	pid = fork();
	if (pid == 0)
		pid = exec_is_not_end(argv, fd, r, pid);
	sig_ign();
	if (in != 0)
		close(in);
	close(fd[1]);
	return (fd[0]);
}

static int	is_end(char **argv, int in, t_redirection *r)
{
	int	pid;

	sig_handler();
	if (r->in == STDIN_FILENO)
		r->in = in;
	r->fd_pipe = -1;
	if (check_is_exec(argv[0], r) == 0)
		return (-1);
	if ((pid = is_builtin(argv, r)) == -1)
		pid = add_pipe_process(argv, r);
	sig_ign();
	close(in);
	return (pid);
}

static int	prepare_is_end(char **cpy_argv, int in, t_redirection *r)
{
	int	ret;

	ret = 0;
	in = is_end(cpy_argv, in, r);
	while (waitpid(in, &ret, 0) != -1)
		continue ;
	if (in != -1 && (!(ret == 2 && check_last_command() == 0)))
		gest_return(ret);
	else if (ret == 2 && check_last_command() == 0)
		gest_return(130);
	in = 0;
	return (in);
}

int			ft_pipe(char **argv, t_token *token, int end_pipe)
{
	t_redirection	*r;
	static int		in;
	char			**cpy_argv;

	cpy_argv = ft_arraydup(argv);
	parser_var(&cpy_argv);
	if (check_last_command() == -1)
	{
		ft_arraydel(&cpy_argv);
		gest_return(1);
		return (-1);
	}
	r = fill_redirection(token);
	if (end_pipe == 0)
		in = is_not_end(cpy_argv, in, r);
	else
		in = prepare_is_end(cpy_argv, in, r);
	delete_redirection(&r);
	ft_arraydel(&cpy_argv);
	return (0);
}
