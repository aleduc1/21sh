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

int			exec_pipe(t_process *p, int in, int out)
{
	char	**environ;
	char	*str;

	str = is_in_path(p->av[0]);
	if (!str)
	{
		gest_return(gest_error_path(p->av[0], p->r));
		return (-1);
	}
	if (p->r->in == STDIN_FILENO)
		p->r->in = in;
	if (p->r->out == STDOUT_FILENO)
		p->r->out = out;
	environ = create_list_env(get_env(0, NULL), 0);
	redirection_fd(p->r);
	execve(str, p->av, environ);
	ft_dprintf(p->r->error, "21sh: command not found: %s\n", p->av[0]);
	ft_arraydel(&environ);
	ft_strdel(&str);
	execve("/bin/test", NULL, NULL);
	exit(0);
	return (0);
}

int			ft_pipe(char **argv, t_token *token, int end_pipe)
{
	static t_process	*p;
	t_redirection		*r;
	char				**cpy_argv;

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
		p = init_process();
	add_process_s(p, cpy_argv, r);
	if (end_pipe == 2)
	{
		act_p_prepare(p);
		delete_process(&p);
		p = NULL;
	}
	ft_arraydel(&cpy_argv);
	return (0);
}
