/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 23:23:34 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/07 01:37:47 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

t_redirection	*init_redirection(void)
{
	t_redirection	*r;

	if (!(r = (t_redirection*)malloc(sizeof(t_redirection) * 1)))
		return (NULL);
	r->in = STDIN_FILENO;
	r->out = STDOUT_FILENO;
	r->error = STDERR_FILENO;
	return (r);
}

t_redirection	*fill_redirection(t_token *t)
{
	int				num_src;
	int				num_dest;
	t_lex			*h;
	t_redirection	*r;

	h = t->command;
	r = init_redirection();
	while (h)
	{
		if (h->token->type == REDIR && h->redir)
		{
			num_src = ft_atoi(h->redir->src_fd[0]);
			num_dest = ft_atoi(h->redir->dest_fd);
			if (num_src == STDIN_FILENO)
				r->in = num_dest;
			else if (num_src == STDOUT_FILENO)
				r->out = num_dest;
			else if (num_src == STDERR_FILENO)
				r->error = num_dest;
		}
		h = h->next;
	}
	return (r);
}

void			delete_redirection(t_redirection **r)
{
	ft_memdel((void**)&r);
}
