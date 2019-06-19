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

/*
** in -> STDIN_FILENO
** out -> STDOUT_FILENO
** error -> STDERR_FILLENO
*/

static void	redir_in(t_redirection *r)
{
	if (r->in != STDIN_FILENO)
		dup2(r->in, STDIN_FILENO);
}

static void	redir_out(t_redirection *r)
{
	if (r->out != STDOUT_FILENO)
		dup2(r->out, STDOUT_FILENO);
}

static void	redir_error(t_redirection *r)
{
	if (r->error != STDERR_FILENO)
		dup2(r->error, STDERR_FILENO);
}

/*
** static void	other_redir(int src, int new_fd)
** {
** 	if (src != new_fd)
** 	{
** 		ft_printf("base = %d, new = %d\n", src, new_fd);
** 		dup2(src, new_fd);
** 		if (verif_close(src))
** 			close(src);		
** 		// dup2(new_fd, src);
** 		// if (verif_close(new_fd))
** 		// 	close(new_fd);
** 	}
** }
*/

static void	standard_redirection(t_redirection *r)
{
	if (r->fd_pipe >= 0)
		close(r->fd_pipe);
	if (r->in != STDIN_FILENO
		&& ft_fd_redirect_exist(r->redirect, STDIN_FILENO) == 0)
	{
		dup2(r->in, STDIN_FILENO);
		close(r->in);
	}
	if (r->out != STDOUT_FILENO
		&& ft_fd_redirect_exist(r->redirect, STDOUT_FILENO) == 0)
	{
		dup2(r->out, STDOUT_FILENO);
		close(r->out);
	}
	if (r->error != STDERR_FILENO
		&& ft_fd_redirect_exist(r->redirect, STDERR_FILENO) == 0)
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
			else if (STDOUT_FILENO == lst->base)
				redir_out(r);
			else if (STDERR_FILENO == lst->base)
				redir_error(r);
			// else
			// 	other_redir(lst->base, lst->new_fd);
		}
		lst = lst->next;
	}
	standard_redirection(r);
	if (verif_close(r->in) && ft_fd_redirect_exist(r->redirect, STDIN_FILENO))
		close(r->in);
	if (verif_close(r->out) && ft_fd_redirect_exist(r->redirect, STDOUT_FILENO))
		close(r->out);
	if (verif_close(r->error)
		&& ft_fd_redirect_exist(r->redirect, STDERR_FILENO))
		close(r->error);
}
