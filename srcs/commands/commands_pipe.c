/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 10:50:50 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/09 00:27:02 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

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
	signal(SIGPIPE, NULL);
	r->out = choice_fd(r->out, pipes[1], STDOUT_FILENO);
	if ((pids = is_builtin(argv, r)) == -1)
		pids = add_process(argv, &return_code, r);
		kill(pids, SIGPIPE);
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
	signal(SIGPIPE, NULL);
		if ((return_code = is_builtin(argv, r)) == -1)
			pids = add_process(argv, &return_code, r);
		close_file_command(token->command, &r);
		gest_return(return_code);
		kill(pids, SIGPIPE);
	}
	else
		in = ft_pipe_b(argv, token, r);
	return (0);
}
