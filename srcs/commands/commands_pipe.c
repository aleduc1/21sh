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

int			add_pipe_process(char **cmd, t_redirection *r)
{
	pid_t	pid;
	char	**environ;
	char	*str;

	str = is_in_path(cmd[0]);
	if (!str)
	{
		ft_dprintf(r->error, "21sh: command not found: %s\n", cmd[0]);
		gest_return(127);
		return (-1);
	}
	pid = fork();
	environ = create_list_env(get_env(0, NULL), 0);
	if (pid == 0)
	{
		sig_dfl();
		redirection_fd(r);
		execve(str, cmd, environ);
		ft_dprintf(r->error, "21sh: command not found: %s\n", cmd[0]);
		execve("/bin/test", NULL, NULL);
		exit(0);
	}
	ft_arraydel(&environ);
	ft_strdel(&str);
	return (pid);
}

static int	is_not_end(char **argv, int in, t_redirection *r)
{
	int		fd[2];
	pid_t	pid;

	sig_handler();
	pipe(fd);
	if (check_is_exec(argv[0], r) == 0)
		return (-1);
	if (r->in == STDIN_FILENO)
		r->in = in;
	r->fd_pipe = fd[0];
	pid = fork();
	if (pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		if (r->out == STDOUT_FILENO)
			r->out = fd[1];
		if ((pid = is_builtin(argv, r)) == -1)
			pid = add_pipe_process(argv, r);
		execve("/bin/test", NULL, NULL);
	}
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
	if (check_is_exec(argv[0], r) == 0)
		return (-1);
	if (r->in == STDIN_FILENO)
		r->in = in;
	r->fd_pipe = -1;
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
	if (in != -1)
		gest_return(in);
	in = 0;
	while (waitpid(in, &ret, 0) != -1)
		continue ;
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
