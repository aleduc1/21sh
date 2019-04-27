/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 12:42:19 by mbellaic          #+#    #+#             */
/*   Updated: 2019/04/27 15:04:21 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

void	dpush_args(t_args **head, char *arg)
{
	t_args	*new_node;

	new_node = (t_args*)malloc(sizeof(t_args));
	new_node->arg = ft_strdup(arg);
	new_node->next = (*head);
	new_node->prev = NULL;
	if ((*head) != NULL)
		(*head)->prev = new_node;
	(*head) = new_node;
}

t_std	*init_std(int fd, char *filename, int append)
{
	t_std	*std;

	if (!(std = (t_std*)malloc(sizeof(t_std) * 1)))
		return (NULL);
	std->fd = fd;
	std->filename = filename;
	std->append = append;
	return (std);
}

t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	if (!(cmd = (t_cmd*)malloc(sizeof(t_cmd) * 1)))
		return (NULL);
	cmd->in = init_std(0, NULL, 0);
	cmd->out = init_std(1, NULL, 0);
	cmd->err = init_std(2, NULL, 0);
	cmd->argv = NULL;
	cmd->heredoc = NULL;
	cmd->next = NULL;
	return (cmd);
}
