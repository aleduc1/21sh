/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 10:50:50 by sbelondr          #+#    #+#             */
/*   Updated: 2019/06/13 22:29:20 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int			verif_close(int fd)
{
	if (fd == STDIN_FILENO || fd == STDOUT_FILENO || fd == STDERR_FILENO ||
			(fd > -1 && fd < 3))
		return (0);
	return (1);
}

/*
** in -> STDIN_FILENO
** out -> STDOUT_FILENO
** error -> STDERR_FILLENO
*/

static void	redir_in(t_redirection *r)
{
	if (r->in != STDIN_FILENO)
	{
		dup2(r->in, STDIN_FILENO);
		if (verif_close(r->in))
			close(r->in);
	}
}

static void	redir_out(t_redirection *r)
{
	if (r->out != STDOUT_FILENO)
	{
		dup2(r->out, STDOUT_FILENO);
		if (verif_close(r->out))
			close(r->out);
	}
}

static void	redir_error(t_redirection *r)
{
	if (r->error != STDERR_FILENO)
	{
		dup2(r->error, STDERR_FILENO);
		if (verif_close(r->error))
			close(r->error);
	}
}

static void	standard_redirection(t_redirection *r)
{
	if (r->fd_pipe >= 0)
		close(r->fd_pipe);
	if (r->in != STDIN_FILENO &&
			ft_fd_redirect_exist(r->redirect, STDIN_FILENO) == 0)
	{
		dup2(r->in, STDIN_FILENO);
		close(r->in);
	}
	if (r->out != STDOUT_FILENO &&
			ft_fd_redirect_exist(r->redirect, STDOUT_FILENO) == 0)
	{
		dup2(r->out, STDOUT_FILENO);
		close(r->out);
	}
	if (r->error != STDERR_FILENO &&
			ft_fd_redirect_exist(r->redirect, STDERR_FILENO) == 0)
	{
		dup2(r->error, STDERR_FILENO);
		close(r->error);
	}
}

void		redirection_fd(t_redirection *r)
{
	t_redirect	*lst;

	lst = r->redirect;
	while (lst)
	{
		if (lst->base != -1)
		{
			if (STDIN_FILENO == lst->base)
				redir_in(r);
			if (STDOUT_FILENO == lst->base)
				redir_out(r);
			if (STDERR_FILENO == lst->base)
				redir_error(r);
		}
		lst = lst->next;
	}
	standard_redirection(r);
}
