/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 10:02:21 by skuppers          #+#    #+#             */
/*   Updated: 2018/11/09 19:31:13 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_list		*create_fd_buffer(int fd)
{
	t_list			*new;

	if (!(new = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	new->content_size = fd;
	if (!(new->content = ft_strnew(1)))
	{
		free(new);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}

static t_list		*get_block(t_list *liste, int fd)
{
	t_list			*tmp;

	tmp = liste;
	while (tmp != NULL)
	{
		if ((int)tmp->content_size == fd)
			break ;
		tmp = tmp->next;
	}
	if (tmp == NULL)
	{
		if ((tmp = create_fd_buffer(fd)) == NULL)
			return (NULL);
		else
			ft_lstextend(liste, tmp);
	}
	return (tmp);
}

static int			cut(t_list *blk, char **line, char *tmp, char **buffer)
{
	int				index;

	if (blk == NULL || tmp == NULL)
		return (0);
	ft_strdel(buffer);
	index = ft_strnchr(tmp, '\n');
	*line = ft_strsub(tmp, 0, index);
	ft_strdel((char**)&(blk)->content);
	blk->content = ft_strsub(tmp, index + 1,
			ft_strlen(tmp) - (index + 1));
	ft_strdel(&tmp);
	return (1);
}

static int			init(int fd, char **line, char **buffer)
{
	if (fd < 0 || line == NULL)
		return (-1);
	if (!(*buffer = ft_strnew(BUFF_SIZE)))
		return (-1);
	return (1);
}

int					get_next_line(int fd, char **line)
{
	int				rd;
	char			*buffer;
	static t_list	*t_buff;
	char			*tmp;

	if (!init(fd, line, &buffer))
		return (-1);
	if (!t_buff)
		if (!(t_buff = create_fd_buffer(fd)))
			return (-1);
	if ((get_block(t_buff, fd)->content) == NULL)
		return (0);
	rd = 1;
	tmp = ft_strdup(get_block(t_buff, fd)->content);
	while (rd > 0 && !(ft_strchr(tmp, '\n')))
	{
		if ((rd = read(fd, buffer, BUFF_SIZE)) < 0)
			return (-1);
		tmp = ft_strjoinfree(tmp, buffer, 1);
		ft_bzero(buffer, BUFF_SIZE);
	}
	if (!(cut(get_block(t_buff, fd), line, tmp, &buffer)))
		return (-1);
	return (ft_strlen(*line) != 0 ||
			get_block(t_buff, fd)->content != NULL) ? 1 : 0;
}
