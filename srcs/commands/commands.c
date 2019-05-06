/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 10:50:50 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/06 06:12:18 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/env.h"

/*
** &
** num_process: processus en cours (le mettre a un 1 quand on appel
** ft_ampersand)
*/
/*
int		background_process(t_cmd *cmds, t_env *my_env, int num_process)
{
	int	result;
	int	pid;

	pid = fork();
	if (pid > 0)
	{
		ft_printf("[%d] %d\n", num_process, pid);
		ft_ampersand(cmds->next, ++num_process, &(my_env));
	}
	waitpid(pid, &result, 0);
	if (pid == 0)
	{
		result = is_builtin(cmds, &my_env);
		if (result == -1)
			add_process(cmds, my_env, &result);
		execve("/bin/test", NULL, NULL);
		exit(pid);
	}
	return (pid);
}

int		ft_ampersand(t_cmd *cmds, int num_process, t_env **my_env)
{
	int	result;

	result = 0;
	if (cmds->next)
	{
		signal(SIGTTOU, NULL);
		result = background_process(cmds, *my_env, num_process);
		if (result != -1)
		{
			ft_printf("[%d] Done\t%s\n", num_process, cmds->argv[0]);
			kill(result, SIGTTOU);
		}
	}
	else
	{
		result = is_builtin(cmds, &(*my_env));
		if (result == -1)
			add_process(cmds, *my_env, &result);
	}
	return (result);
}



int		ft_ampersand_double(t_cmd *cmds, t_env **my_env)
{
	int	check;

	check = 0;
	while (cmds && check != -1 && check != 256)
	{
		check = ft_simple_command(cmds, &(*my_env));
		cmds = cmds->next;
	}
	return (check);
}*/

/*
** |
*/

int		choice_fd(t_token *lex, int fd, int origin)
{
	t_lex	*head;

	head = lex->command;
	while (head)
	{
		if (head->token->type == REDIR && ft_atoi(head->redir->src_fd[0]) == origin)
		{
			if (ft_atoi(head->redir->dest_fd) == -1)
			{
				head->redir->dest_fd = ft_itoa(fd);
				return (1);
			}
			return (0);
		}
		head = head->next;
	}
	return (-1);
}

int		ft_pipe(char **argv, t_token *lex, int end_pipe)
{
	static int	in;
	int	return_code;
	int	pids;
	int	pipes[2];

	if (choice_fd(lex, in, STDIN_FILENO) == -1)
		dprintf(2, "Error function choice_fd\n");
	if (end_pipe)
	{
		if ((return_code = is_builtin(argv, lex->command)) == -1)
			pids = add_process(argv, lex, &return_code);
		close_file_command(lex->command);
		gest_return(return_code);
	}
	else
	{
		pipe(pipes);
		if (choice_fd(lex, pipes[1], STDOUT_FILENO) == -1)
			dprintf(2, "Error function choice_fd\n");
		if ((pids = is_builtin(argv, lex->command)) == -1)
			pids = add_process(argv, lex, &return_code);
		close(pipes[1]);
		close_file_command(lex->command);
		in = pipes[0];
	}
	return (0);
}

/*
** ||
*/
/*
int		ft_pipe_double(t_cmd *cmds, t_env **my_env)
{
	int	check;

	check = -1;
	while (cmds && (check == -1 || check == 256))
	{
		check = ft_simple_command(cmds, &(*my_env));
		cmds = cmds->next;
	}
	return (check);
}*/

/*
** simple command
*/

int		ft_simple_command(char **argv, t_token *lex)
{
	int		verif;

	if ((verif = is_builtin(argv, lex->command)) == -1)
		verif = exec_fork(argv, lex);
	close_file_command(lex->command);
	gest_return(verif);
	return (verif);
}
