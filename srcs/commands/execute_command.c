/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 08:43:53 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/06 22:46:28 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "env.h"
#include "../../includes/env.h"

/*
** in -> STDIN_FILENO
** out -> STDOUT_FILENO
** error -> STDERR_FILLENO
*/

void	open_redirection(t_token *lex)
{
	t_lex	*head;

	head = lex->command; // tempo a changer + tard
	while (head)
	{
		if (head->token->type == REDIR)// && lex->redir)
			{
				ft_putendl(head->redir->src_fd[0]);
				ft_putendl(head->redir->dest_fd);
dup2(ft_atoi(head->redir->dest_fd), ft_atoi(head->redir->src_fd[0]));
			}
			
		head = head->next;
	}
}

int		add_process(char **cmd, t_token *lex, int *returns_code)
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
		open_redirection(lex);
		execve(cmd[0], cmd, env);
		dprintf(STDERR_FILENO, "21sh: %s: No such file or directory\n", cmd[0]);
		exit(pid);
	}
	ft_arraydel(&env);
	return (pid);
}

int		exec_fork(char **cmd, t_token *lex)
{
	int	return_code;
	int	pid;

	signal(SIGINT, NULL);
	pid = add_process(cmd, lex, &return_code);
	if (pid != -1)
		kill(pid, SIGINT);
	return (return_code);
}
