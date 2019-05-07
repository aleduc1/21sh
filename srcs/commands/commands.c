/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 10:50:50 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/07 01:42:02 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

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

int		choice_fd(int origin, int fd, int default_fd)
{
	if (origin == default_fd)
		return (fd);
	return (origin);
}

int		ft_pipe(char **argv, t_token *lex, int end_pipe)
{
	static int		in;
	int				return_code;
	int				pids;
	int				pipes[2];
	t_redirection	*r;

	r = fill_redirection(lex);
	r->in = choice_fd(r->in, in, STDIN_FILENO);
	if (end_pipe)
	{
		if ((return_code = is_builtin(argv, r)) == -1)
			pids = add_process(argv, lex, &return_code, r);
		close_file_command(lex->command, &r);
		gest_return(return_code);
	}
	else
	{
		pipe(pipes);
		r->out = choice_fd(r->out, pipes[1], STDOUT_FILENO);
		if ((pids = is_builtin(argv, r)) == -1)
			pids = add_process(argv, lex, &return_code, r);
		close(pipes[1]);
		close_file_command(lex->command, &r);
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
	t_redirection	*r;
	int				verif;

	r = fill_redirection(lex);
	if ((verif = is_builtin(argv, r)) == -1)
		verif = exec_fork(argv, lex, r);
	close_file_command(lex->command, &r);
	gest_return(verif);
	return (verif);
}
