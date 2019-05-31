/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 08:32:42 by mbellaic          #+#    #+#             */
/*   Updated: 2019/05/27 18:31:24 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void		history_file(t_node *history)
{
	t_node	*cursor;
	int fd;

	cursor = history;
	fd = open(".history", O_RDWR | O_CREAT, 0666);
	while (cursor->next)
		cursor = cursor->next;
	while (cursor->prev)
	{
		write(fd, cursor->line, ft_strlen(cursor->line));
		write(fd, "\n", 1);
		cursor = cursor->prev;
	}
	close (fd);
}

void		file_to_history(t_pos *pos)
{
	int		fd;
	char	*history_line;

	history_line = NULL;
	fd = open(".history", O_RDWR | O_CREAT, 0666);
	while (get_next_line(fd, &history_line) > 0)
	{
		inserthistory(pos->history, history_line, pos);
		pos->historysum++;
		ft_strdel(&history_line);
	}
}
