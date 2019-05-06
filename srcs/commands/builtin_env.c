/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 17:36:44 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/06 04:15:00 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/env.h"

int		return_good_fd(t_lex *lex, int fd)
{
	int		final;
	t_lex	*head;

	final = -1;
	head = lex;
	while (lex)
	{
		if (lex->redir->src_fd == fd)
			final = (lex->redir->dest_fd != -1) ? lex->redir->dest_fd : lex->redir->src_fd;
		lex = lex->next;
	}
	lex = head;
	return (final);
}

int		builtin_env(t_lex *lex)
{
	int		i;
	int		fd;
	char	**lst_env;

	fd = return_good_fd(lex, STDOUT_FILENO);
	lst_env = create_list_env(get_env(), 1);
	i = -1;
	while (lst_env[++i])
		ft_dprintf(fd, "%s\n", lst_env[i]);
	ft_arraydel(&lst_env);
	return (0);
}

int		builtin_set(t_lex *lex)
{
	int		i;
	int		fd;
	char	**lst_env;

	fd = return_good_fd(lex, STDOUT_FILENO);
	lst_env = create_list_env(get_env(), 0);
	i = -1;
	while (lst_env[++i])
		ft_dprintf(fd, "%s\n", lst_env[i]);
	ft_arraydel(&lst_env);
	return (0);
}
