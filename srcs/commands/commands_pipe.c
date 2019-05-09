/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 10:50:50 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/09 05:22:33 by sbelondr         ###   ########.fr       */
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

	pids = 0;
	parser_var(&argv);
	r = fill_redirection(token);
	r->in = choice_fd(r->in, in, STDIN_FILENO);
	if (end_pipe)
	{
		if ((return_code = is_builtin(argv, r)) == -1)
			pids = add_process(argv, &return_code, r);
		waitpid(pids, &return_code, 0);
		while(wait(&return_code) != -1)
			continue ;
		close_file_command(token->command, &r);
		gest_return(return_code);
	}
	else
		in = ft_pipe_b(argv, token, r);
	return (0);
}
