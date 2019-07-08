/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 16:44:29 by sbelondr          #+#    #+#             */
/*   Updated: 2019/07/08 08:30:32 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

/*
** F_OK: file exist
*/

int			test_quote(char *name)
{
	int		fd;
	int		len;
	char	*dst;

	dst = NULL;
	len = ft_strlen(name) - 1;
	if (name[0] == '"' || name[0] == '\'')
		if (name[len] == '"' || name[len] == '\'')
			dst = ft_strsub(name, 1, len - 1);
	if (!dst)
		return (-1);
	if (access(dst, F_OK) != -1)
	{
		ft_strdel(&dst);
		return (0);
	}
	fd = open(dst, O_RDWR | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	ft_strdel(&dst);
	if (fd != -1)
	{
		close(fd);
		return (1);
	}
	return (-1);
}

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
	if ((fd = test_quote(name)) != -1)
		return (fd);
	ft_printf("21sh: error create file: %s\n", name);
	return (-1);
}

/*
** O_TRUNC -> remove data in file
*/

static int	open_file_great(t_redir *redir)
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
	else if (redir->type == GREAT || redir->type == DLESS
		|| redir->type == AMPGREAT || redir->type == GREATAMP)
		redir->dest_fd = ft_itoa(open(redir->filename, O_RDWR | O_TRUNC));
	else
		redir->dest_fd = ft_itoa(open(redir->filename, O_RDWR));
	return (1);
}

static int	open_file_dless(t_redir *redir, t_pos *pos)
{
	int		fd;
	char	*name;
	char	*str;
	char	*tmp;

	if (!(redir->heredoc))
		return (-1);
	name = ft_strdup("/tmp/.21sh0");
	redir->filename = name;
	tmp = ft_strdup(redir->heredoc);
	str = heredoc(tmp, pos);
	if (!str)
		return (-1);
	ft_remove_last_chr(&str);
	fd = file_exist(name);
	(fd > -1) ? fd = open_file_great(redir) : 0;
	if (fd <= -1)
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
		if (lex->token->type == REDIR && lex->redir
			&& lex->redir->dest_fd
			&& ft_atoi(lex->redir->dest_fd) != -1)
			if (lex->redir->filename || lex->redir->close == 1)
				close(ft_atoi(lex->redir->dest_fd));
		lex = lex->next;
	}
	lex = head;
	if (r && (*r))
		delete_redirection(&(*r));
	return (0);
}

/*
** pos -> pour les heredocs
** LESS -> <
** DLESS -> <<
** GREAT -> >
** DGREAT -> >>
** AMPGREAT -> &>
** GREATAMP -> >&
** AMPLESS -> <&
** LESSAMP -> &<
*/

int			open_file_command(t_redir *redir, t_pos *pos)
{
	if (redir->type == GREAT || redir->type == DGREAT || redir->type == LESS
		|| redir->type == AMPGREAT || redir->type == AMPLESS
		|| redir->type == LESSAMP || redir->type == GREATAMP)
		open_file_great(redir);
	else if (redir->type == DLESS)
		open_file_dless(redir, pos);
	return (0);
}
