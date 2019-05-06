/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 16:44:29 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/06 02:52:28 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/env.h"

/*
** F_OK: file exist
*/

static int	file_exist(char *name)
{
	int	fd;

	if (access(name, F_OK) != -1)
		return (0);
	fd = open(name, O_RDWR | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd != -1)
	{
		close(fd);
		return (1);
	}
	ft_dprintf(2, "21sh: error create file: %s\n", name);
	return (-1);
}

int			open_file_great(t_redir *redir)
{
	if (redir->filename)
		redir->dest_fd = file_exist(redir->filename);
	else
		return (0);
	if (redir->dest_fd == -1)
		return (-1);
	if (redir->type == DGREAT)
		redir->dest_fd = get_end_line(redir->filename);
	else
		redir->dest_fd = open(redir->filename, O_RDWR | O_TRUNC);
	return (1);
}

int			open_file_dless(t_redir *redir)
{
	int		len;
	int		index;
	char	*name;

	if (!heredoc)
		return (-1);
	name = ft_strdup("/tmp/.21sh0");
	len = ft_strlen(name) - 1;
	index = -1;
	while ((redir->dest_fd = open(name, O_RDWR | O_TRUNC)) == -1)
	{
		name[len] = name[len] + 1;
		if (++index > 8)
		{
			ft_strdel(&name);
			return (-1);
		}
	}
	redir->filename = name;
	ft_dprintf(redir->dest_fd, "%s", redir->heredoc);
	return (1);
}

int			close_file_command(t_lex *lex)
{
	t_lex	*head;

	head = lex;
	while (lex)
	{
		if (lex->token->type == REDIR && lex->redir && lex->redir->dest_fd != -1)
			close(lex->redir->dest_fd);
		lex = lex->next;
	}
	lex = head;
	return (0);
}

int			open_file_command(t_redir *redir)
{
	if (redir->type == GREAT || redir->type == DGREAT || redir->type == LESS)
		open_file_great(redir);
	else if (redir->type == DLESS)
		open_file_dless(redir);
	return (0);
}
