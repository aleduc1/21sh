/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 10:50:50 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/23 15:23:58 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "job.h"

/*
** simple command
*/

/*
** launch_job(j, 0); & continue_job(j, 0); -> &
**
** ps au
*/

int			ft_simple_command(char **argv, t_token *token)
{
	t_redirection	*r;
	int				verif;
	char			**cpy_argv;
	t_job			*j;
	t_process		*p;
	t_job			*h;

	cpy_argv = ft_arraydup(argv);
	verif = 0;
	r = fill_redirection(token);
	parser_var(&cpy_argv);
	j = get_first_job(NULL);
	h = j;
	while (j->pgid != 0)
	{
		ft_printf("je suis la\n");
		j->next = init_job();
		j = j->next;
	}
	p = j->first_process;
	ft_arraydel(&(p->cmd));
	p->cmd = cpy_argv;
	j->r = r;
	if ((verif = is_builtin(cpy_argv, r)) == -1)
	{
		if (is_in_path(&cpy_argv) == 1)
			launch_job(j, 1);
		else
			ft_dprintf(r->error, "21sh: command not found: %s\n",
					p->cmd[0]);
	}
//	close_file_command(token->command, &r);
	gest_return(verif);
	j = h;
	return (verif);
}

/*
** if ((verif = is_builtin(cpy_argv, r)) == -1)
** verif = exec_fork(cpy_argv, r);
*/

/*
** ||
*/

int			ft_pipe_double(char **argv, t_token *token)
{
	int		check;
	char	*str;

	str = value_line_path("?", 0);
	check = ft_atoi(str);
	if (check == -1)
		check = ft_simple_command(argv, token);
	ft_strdel(&str);
	return (check);
}

/*
** &
** num_process: processus en cours (mettre a 1 la premiere fois)
*/

static int	background_process(char **argv, t_token *token)
{
	int		result;
	pid_t	test;

	result = 0;
	if ((test = tcgetpgrp(STDIN_FILENO)) < 0)
		ft_dprintf(STDERR_FILENO, "Error tcgetpgrp\n");
	else
	{
		if (setpgid(getpid(), 0) != 0)
			ft_dprintf(STDERR_FILENO, "Error setpgid\n");
		else
		{
			ft_printf("start pid = %d\n", (int)getpid());
			if (tcsetpgrp(STDIN_FILENO, getpid()) != 0)
				ft_dprintf(STDERR_FILENO, "Error tcsetpgrp\n");
			else if ((test = tcgetpgrp(STDOUT_FILENO)) < 0)
				ft_dprintf(STDERR_FILENO, "Error tcgetpgrp 2\n");
			else
			{
				ft_printf("PID: %d\n", (int)test);
				ft_simple_command(argv, token);
			}
		}
	}
	return (result);
}

int			ft_ampersand(char **argv, t_token *token)
{
	int			result;

	result = 0;
	result = background_process(argv, token);
	if (result != -1)
	{
		ft_printf("[0] Done\t%s\n", argv[0]);
		kill(result, SIGTTOU);
	}
	return (result);
}

// static int	background_process(char **argv, t_token *token, int num_process)
// {
// 	int	result;
// 	int	pid;

// 	pid = fork();
// 	if (pid > 0)
// 		ft_printf("[%d] %d\n", num_process, pid);
// 	waitpid(pid, &result, 0);
// 	if (pid == 0)
// 	{
// 		ft_simple_command(argv, token);
// 		execve("/bin/test", NULL, NULL);
// 		exit(pid);
// 	}
// 	return (pid);
// }

// int			ft_ampersand(char **argv, t_token *token, int num_process)
// {
// 	int	result;

// 	result = 0;
// 	signal(SIGTTOU, NULL);
// 	result = background_process(argv, token, num_process);
// 	if (result != -1)
// 	{
// 		ft_printf("[%d] Done\t%s\n", num_process, argv[0]);
// 		kill(result, SIGTTOU);
// 	}
// 	return (result);
// }

/*
** &&
*/

int			ft_ampersand_double(char **argv, t_token *token)
{
	int		check;
	char	*str;

	str = value_line_path("?", 0);
	check = ft_atoi(str);
	if (check != -1)
		check = ft_simple_command(argv, token);
	ft_strdel(&str);
	return (check);
}
