/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 16:43:54 by sbelondr          #+#    #+#             */
/*   Updated: 2019/04/13 16:44:28 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/env.h"

t_commands	*init_commands(char **commands, int fd_stock[3])
{
	t_commands	*cmds;

	if (!(cmds = (t_commands*)malloc(sizeof(t_commands) * 1)))
		return (NULL);
	cmds->command = ft_arraydup(commands);
	cmds->fd_stock[0] = fd_stock[0];
	cmds->fd_stock[1] = fd_stock[1];
	cmds->fd_stock[2] = fd_stock[2];
	cmds->next = NULL;
	return (cmds);
}

void	delete_commands(t_commands **cmds)
{
	t_commands	*tmp;

	while (*cmds)
	{
		tmp = *cmds;
		*cmds = (*cmds)->next;
		ft_arraydel(&(tmp->command));
		free(tmp);
		tmp = NULL;
	}
}
