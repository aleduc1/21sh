/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 16:44:29 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/07 01:08:31 by sbelondr         ###   ########.fr       */
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
	printf("21sh: error create file: %s\n", name);
	return (-1);
}

int			open_file_great(t_redir *redir)
{
	if (redir->filename)
		redir->dest_fd = ft_itoa(file_exist(redir->filename));
	else
		return (0);
	if (ft_atoi(redir->dest_fd) == -1)
		return (-1);
	if (redir->type == DGREAT)
		redir->dest_fd = ft_itoa(get_end_line(redir->filename));
	else
		redir->dest_fd = ft_itoa(open(redir->filename, O_RDWR | O_TRUNC));
	return (1);
}

void		remove_last_chr(char **str)
{
	int		i;
	int		len;
	int		index;
	char	*tmp;

	i = -1;
	len = ft_strlen(*str);
	while ((*str)[++i] && i < (len - 1))
		if ((*str)[i] == '\n')
			index = i;
	tmp = ft_strsub((*str), 1, index);
	ft_strdel(&(*str));
	(*str) = tmp;
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
	remove_last_chr(&str);
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

int			close_file_command(t_lex *lex)
{
	t_lex	*head;

	head = lex;
	while (lex)
	{
		if (lex->token->type == REDIR && lex->redir && ft_atoi(lex->redir->dest_fd) != -1)
			close(ft_atoi(lex->redir->dest_fd));
		lex = lex->next;
	}
	lex = head;
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
