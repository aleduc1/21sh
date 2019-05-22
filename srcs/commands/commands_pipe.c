/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 10:50:50 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/21 15:34:36 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	redirection_fd_pipe(t_redirection *r)
{
	if (r->fd_pipe >= 0)
		close(r->fd_pipe);
	if (r->in != STDIN_FILENO)
	{
		dup2(r->in, STDIN_FILENO);
		close(r->in);
	}
	if (r->out != STDOUT_FILENO)
	{
		dup2(r->out, STDOUT_FILENO);
		close(r->out);
	}
	if (r->error != STDERR_FILENO)
	{
		dup2(r->error, STDERR_FILENO);
		close(r->error);
	}
}

int			add_pipe_process(char **cmd, t_redirection *r)
{
	pid_t	pid;
	char	**environ;

	if (is_in_path(&cmd) != 1)
	{
		ft_dprintf(r->error, "21sh: command not found: %s\n", cmd[0]);
		return (-1);
	}
	pid = fork();
	environ = create_list_env(get_env(0, NULL), 0);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		redirection_fd_pipe(r);
		execve(cmd[0], cmd, environ);
		ft_dprintf(r->error, "21sh: command not found: %s\n", cmd[0]);
		execve("/bin/test", NULL, NULL);
		exit(0);
	}
	ft_arraydel(&environ);
	return (pid);
}

static int	is_not_end(char **argv, int in, t_redirection *r)
{
	int		fd[2];
	pid_t	pid;

	signal(SIGINT, sighandler);
	signal(SIGQUIT, sighandler);
	pipe(fd);
	if (r->out == STDOUT_FILENO)
		r->out = fd[1];
	if (r->in == STDIN_FILENO)
		r->in = in;
	r->fd_pipe = fd[0];
	pid = fork();
	if (pid == 0)
	{
		if ((pid = is_builtin(argv, r)) == -1)
			pid = add_pipe_process(argv, r);
		execve("/bin/test", NULL, NULL);
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (in != 0)
		close(in);
	close(fd[1]);
	return (fd[0]);
}

static int	is_end(char **argv, int in, t_redirection *r)
{
	pid_t	pid;

	signal(SIGINT, sighandler);
	signal(SIGQUIT, sighandler);
	if (r->in == STDIN_FILENO)
		r->in = in;
	r->fd_pipe = -1;
	if ((pid = is_builtin(argv, r)) == -1)
		pid = add_pipe_process(argv, r);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	close(in);
	return (pid);
}

int			ft_pipe(char **argv, t_token *token, int end_pipe)
{
	int				ret;
	static int		in;
	t_redirection	*r;
	char			**cpy_argv;

	cpy_argv = ft_arraydup(argv);
	parser_var(&cpy_argv);
	r = fill_redirection(token);
	if (end_pipe == 0)
		in = is_not_end(cpy_argv, in, r);
	else
	{
		in = is_end(cpy_argv, in, r);
		in = 0;
		while (waitpid(in, &ret, 0) != -1)
			continue ;
		gest_return(ret);
	}
	delete_redirection(&r);
	ft_arraydel(&cpy_argv);
	return (0);
}
