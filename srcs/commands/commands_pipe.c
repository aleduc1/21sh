/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 10:50:50 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/28 11:50:48 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "job.h"

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

static int	is_not_end(t_job *j, t_process *p, int in)
{
	int		fd[2];
	int		pid;

	pipe(fd);
	if (j->r->out == STDOUT_FILENO)
		j->r->out = fd[1];
	if (j->r->in == STDIN_FILENO)
		j->r->in = in;
	j->r->fd_pipe = fd[0];
	pid = fork();
	if (pid == 0)
	{
		if ((pid = is_builtin(j)) == -1)
		{
			if (is_in_path(&p->cmd) == 1)
				pid = launch_job(j, 1);
			else
				display_error_command(j->r, p->cmd);
		}
		execve("/bin/test", NULL, NULL);
	}
	if (in != 0)
		close(in);
	close(fd[1]);
	return (fd[0]);
}

static int	is_end(t_job *j, t_process *p, int in)
{
	int	verif;

	dfl_signaux();
	if (j->r->in == STDIN_FILENO)
		j->r->in = in;
	j->r->fd_pipe = -1;
	if ((verif = is_builtin(j)) == -1)
	{
		if (is_in_path(&p->cmd) == 1)
			verif = launch_job(j, 1);
		else
			display_error_command(j->r, p->cmd);
	}
	close(in);
	return (verif);
}

t_process		*edit_lst_process(char **argv, t_job **j)
{
	t_process		*p;
	int				process_id;

	(*j) = get_first_job(NULL);
	process_id = 0;
	while ((*j)->next)
		(*j) = (*j)->next;
	p = (*j)->first_process;
	while (p)
	{
		if (p->next)
			p = p->next;
		else
		{
			p->next = init_process();
			break ;
		}		
	}
	p = p->next;
	p->cmd = ft_arraydup(argv);
	p->process_id = process_id + 1;
	parser_var(&p->cmd);
	return (p);
}

t_process	*job_to_pipe(char **av, t_token *t, int end_pipe, t_job **j)
{
	t_process	*p;

	/*if (end_pipe == 0)
	{
		(*j) = edit_lst_job(av, t, NULL);
		return ((*j)->first_process);
	}
	else*/
		p = edit_lst_process(av, j);
	return (p);
}

int			ft_pipe(char **argv, t_token *t, int end_pipe)
{
	int		in;
	t_job			*j;
	t_process		*p;
	int				ret;

	p = job_to_pipe(argv, t, end_pipe, &j);
	if (end_pipe == 2)
	{
		j->pgid = fork();
		if (j->pgid == 0)
		{
			in = 0;
			while (j)
			{
				p = j->first_process;
				in = is_not_end(j, p, in);
				j = j->next;
				if (!j->next)
					break ;
			}
			in = is_end(j, p, in);
			wait_for_jobs(j);
			gest_return(in);
			execve("/bin/test", NULL, NULL);
			while (wait(&ret))
				continue ;
		}
	}
	/*if (end_pipe == 0 || end_pipe == 1)
		in = is_not_end(j, p, in);
	else
	{
		in = is_end(j, p, in);
		wait_for_jobs(j);
		gest_return(in);
		in = 0;
	}*/
	if ((p->completed == 1 || p->pid == 0) && end_pipe == 2)
	{
	//	close_file_command(t->command, &j->r);
	//	clean_fuck_list();
	}
	return (0);
}
