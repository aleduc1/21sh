/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 16:44:29 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/08 16:47:58 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/env.h"

/*
** F_OK: file exist
*/

int			file_exist(char *name)
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
	printf("21sh: error create file: %s\n", name);
	return (-1);
}

/*
** O_TRUNC -> remove data in file
*/

int			open_file_great(t_redir *redir)
{
	if (redir->filename)
		redir->dest_fd = ft_itoa(file_exist(redir->filename));
	else
		return (0);
	if (ft_atoi(redir->dest_fd) == -1)
		return (-1);
	ft_strdel(&redir->dest_fd);
	if (redir->type == DGREAT)
		redir->dest_fd = ft_itoa(get_end_line(redir->filename));
	else if (redir->type == GREAT)
		redir->dest_fd = ft_itoa(open(redir->filename, O_RDWR | O_TRUNC));
	else if (redir->type == DLESS)
		redir->dest_fd = ft_itoa(open(redir->filename, O_RDWR | O_TRUNC));
	else
		redir->dest_fd = ft_itoa(open(redir->filename, O_RDWR));
	return (1);
}

int			open_file_dless(t_redir *redir, t_pos *pos)
{
	int		fd;
	char	*name;
	char	*str;

	if (!(redir->heredoc))
		return (-1);
	name = ft_strdup("/tmp/.21sh0");
	redir->filename = name;
	str = heredoc(redir->heredoc, pos);
	ft_remove_last_chr(&str);
	fd = file_exist(name);
	if (fd > -1)
		fd = open_file_great(redir);
	else
		return (-1);
	ft_dprintf(ft_atoi(redir->dest_fd), "%s", str);
	close(ft_atoi(redir->dest_fd));
	ft_strdel(&(redir->dest_fd));
	redir->dest_fd = ft_itoa(open(redir->filename, O_RDWR));
	ft_strdel(&str);
	return (1);
}

int			close_file_command(t_lex *lex, t_redirection **r)
{
	t_lex	*head;

	head = lex;
	while (lex)
	{
		if (lex->token->type == REDIR && lex->redir &&
				lex->redir->dest_fd &&
				ft_atoi(lex->redir->dest_fd) != -1)
			if (lex->redir->filename || lex->redir->close == 1)
				close(ft_atoi(lex->redir->dest_fd));
		lex = lex->next;
	}
	lex = head;
	delete_redirection(&(*r));
	return (0);
}

int			open_file_command(t_redir *redir, t_pos *pos)
{
	if (redir->type == GREAT || redir->type == DGREAT || redir->type == LESS)
		open_file_great(redir);
	else if (redir->type == DLESS)
		open_file_dless(redir, pos);
	return (0);
}
