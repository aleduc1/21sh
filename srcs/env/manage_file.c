/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 16:44:29 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/03 13:12:24 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/env.h"

static int	check_is_fd(char *name)
{
	int	fd;

	fd = -1;
	if (name && name[0] == '&')
		fd = ft_atoi(name + 1);
	return (fd);
}

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
	else
		ft_dprintf(2, "21sh: error create file: %s\n", name);
	return (-1);
}

int			open_file(t_env **my_env, char *name, char *fd_out)
{
	int		fd;
	t_arg	*arg;
	char	*fd_str;
	char	**split;

	if ((fd = check_is_fd(name)) == -1)
	{
		split = ft_strsplit(name, ';');
		file_exist(split[0]);
		if ((!split[1]) || split[1][0] == '1')
			fd = get_end_line(split[0]);
		else
			fd = open(split[0], O_RDWR | O_TRUNC);
		ft_arraydel(&split);
	}
	fd_str = ft_itoa(fd);
	arg = create_arg(fd_out, fd_str);
	edit_set(arg, &(*my_env));
	free_arg(&arg);
	ft_strdel(&fd_str);
	return (fd);
}

int			open_file_std(t_std *std)
{
	if (std->fd == -1)
		std->fd = file_exist(std->filename);
	else
		return (0);
	if (std->fd == -2)
		return (-1);
	if (std->append == 1)
		std->fd = get_end_line(std->filename);
	else
		std->fd = open(std->filename, O_RDWR | O_TRUNC);
	return (1);
}

int			close_file_command(t_cmd *cmd)
{
	if (cmd->in->fd != 0)
		close(cmd->in->fd);
	if (cmd->out->fd != 1)
		close(cmd->out->fd);
	if (cmd->err->fd != 2)
		close(cmd->err->fd);
	return (0);
}

int			open_file_command(t_cmd *cmd)
{
	if (open_file_std(cmd->in) == -1)
		return (-1);
	if (open_file_std(cmd->out) == -1)
		return (-1);
	if (open_file_std(cmd->err) == -1)
		return (-1);
	return (0);
}

int			open_file_not_env(char *name, int end_line)
{
	int		fd;
	char	**split;

	if ((fd = check_is_fd(name)) == -1)
	{
		split = ft_strsplit(name, ';');
		file_exist(split[0]);
		if (end_line == 1)
			fd = get_end_line(split[0]);
		else
			fd = open(split[0], O_RDWR | O_TRUNC);
		ft_arraydel(&split);
	}
	return (fd);
}

void		close_file(t_env **my_env)
{
	t_arg	*arg;

	if (search_line_env(*my_env, "FD_FILE_OUTPUT", 0))
	{
		arg = create_arg("FD_OUTPUT", "1");
		edit_set(arg, &(*my_env));
		free_maillon_env(&(*my_env), "FD_FILE_OUTPUT", 0);
		free_arg(&arg);
	}
}

/*
** key = FD_OUTPUT | FD_ERROR_OUTPUT
** int builtin: 1 si on utilise execve donc pas besoin de free (voir man execve)
**				0 close fd
*/

int			dest_output(t_env **my_env)
{
	char	*src;
	int		fd;
	char	*fd_out;

	fd = 0;
	fd_out = ft_strdup("FD_OUTPUT");
	src = value_line_path(*my_env, "FD_FILE_OUTPUT", 0);
	if (!src)
	{
		src = value_line_path(*my_env, fd_out, 0);
		fd = ft_atoi(src);
	}
	else
		fd = open_file(&(*my_env), src, fd_out);
	ft_strdel(&src);
	ft_strdel(&fd_out);
	return (fd);
}

/*
** sortie d'erreur
*/

void		close_error_file(t_env **my_env)
{
	t_arg	*arg;

	if (search_line_env(*my_env, "FD_FILE_ERROR_OUTPUT", 0))
	{
		arg = create_arg("FD_ERROR_OUTPUT", "2");
		edit_set(arg, &(*my_env));
		free_maillon_env(&(*my_env), "FD_FILE_ERROR_OUTPUT", 0);
		free_arg(&arg);
	}
}

int			dest_error_output(t_env **my_env)
{
	char	*fd_out;
	char	*src;
	int		fd;

	fd = 0;
	fd_out = ft_strdup("FD_ERROR_OUTPUT");
	src = value_line_path(*my_env, "FD_FILE_ERROR_OUTPUT", 0);
	if (!src)
	{
		src = value_line_path(*my_env, "FD_ERROR_OUTPUT", 0);
		fd = ft_atoi(src);
	}
	else
		fd = open_file(&(*my_env), src, fd_out);
	ft_strdel(&src);
	ft_strdel(&fd_out);
	return (fd);
}
