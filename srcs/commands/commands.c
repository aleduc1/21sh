/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 10:50:50 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/28 10:00:40 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "job.h"

/*
** simple command
*/

void		display_lst_job(t_job *j)
{
	t_job		*sv;
	t_process	*p;

	sv = j;
	if (!sv)
		return ;
	while (sv)
	{
		ft_printf("===========================\n");
		p = sv->first_process;
		while (p)
		{
			ft_arraydisplay(p->cmd);
			ft_printf("pid = %d\ncompleted = %d\nstopped = %d\nstatus = %d\n",
			p->pid, p->completed, p->stopped, p->status);
			p = p->next;
		}
		ft_printf("pgpid = %d\nnotified = %d\n", sv->pgid, sv->notified);
		sv = sv->next;
		ft_printf("___________________________\n");
	}
}

void		clean_fuck_list(void)
{
	t_job	**j;
	t_job	*last;
	t_job	*next;
	t_job	*h;

	j = static_job();
	h = *j;
	last = NULL;
	while (*j)
	{
		next = (*j)->next;
		if (((*j)->first_process->completed == 1 ||
		(*j)->first_process->pid == 0) && (*j)->first_process->stopped == 0)
		{
			if (last)
				last->next = next;
			else
				h = NULL;
			free_job(&(*j));
		}
		else
			last = (*j);
		(*j) = next;
	}
	(*j) = h;
}

int			ft_simple_command(char **argv, t_token *token)
{
	int				verif;
	t_job			*j;
	t_process		*p;

	verif = 0;
	j = get_first_job(NULL);
	while (j->pgid != 0)
	{
		j->next = init_job();
		j = j->next;
	}
	p = j->first_process;
	p->cmd = ft_arraydup(argv);
	parser_var(&p->cmd);
	j->r = fill_redirection(token);
	if ((verif = is_builtin(p->cmd, j->r)) == -1)
	{
		if (is_in_path(&p->cmd) == 1)
			verif = launch_job(j, 1);
		else
			ft_dprintf(j->r->error, "21sh: command not found: %s\n",
					p->cmd[0]);
	}
	if (p->completed == 1 || p->pid == 0)
	{
		close_file_command(token->command, &j->r);
		clean_fuck_list();
	}
	gest_return(verif);
	return (verif);
}

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

int			ft_ampersand(char **argv, t_token *token)
{
	int				verif;
	t_job			*j;
	t_process		*p;

	verif = 0;
	j = get_first_job(NULL);
	while (j->pgid != 0)
	{
		j->next = init_job();
		j = j->next;
	}
	p = j->first_process;
	p->cmd = ft_arraydup(argv);
	parser_var(&p->cmd);
	j->r = fill_redirection(token);
	if ((verif = is_builtin(p->cmd, j->r)) == -1)
	{
		if (is_in_path(&p->cmd) == 1)
			verif = launch_job(j, 0);
		else
			ft_dprintf(j->r->error, "21sh: command not found: %s\n",
					p->cmd[0]);
	}
	if (p->completed == 1 || p->pid == 0)
	{
		close_file_command(token->command, &j->r);
		clean_fuck_list();
	}
	gest_return(verif);
	return (verif);
}

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
