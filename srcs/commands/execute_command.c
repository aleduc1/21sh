/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 08:43:53 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/06 23:48:07 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

/*
** in -> STDIN_FILENO
** out -> STDOUT_FILENO
** error -> STDERR_FILLENO
*/

void	open_redirection(t_redirection *r)
{
	dup2(r->in, STDIN_FILENO);
	dup2(r->out, STDOUT_FILENO);
	dup2(r->error, STDERR_FILENO);
}

int		add_process(char **cmd, t_token *lex, int *returns_code, t_redirection *r)
{
	char	**env;
	int		pid;

	if (is_in_path(&cmd) != 1)
	{
		*returns_code = -1;
		return (-1);
	}
	env = create_list_env(get_env(0), 0);
	pid = fork();
	waitpid(pid, &(*returns_code), 0);
	if (pid == 0)
	{
		open_redirection(r);
		execve(cmd[0], cmd, env);
		ft_dprintf(STDERR_FILENO, "21sh: command not found: %s\n", cmd[0]);
		exit(pid);
	}
	ft_arraydel(&env);
	return (pid);
}

int		exec_fork(char **cmd, t_token *lex, t_redirection *r)
{
	int	return_code;
	int	pid;

	signal(SIGINT, NULL);
	pid = add_process(cmd, lex, &return_code, r);
	if (pid != -1)
		kill(pid, SIGINT);
	return (return_code);
}