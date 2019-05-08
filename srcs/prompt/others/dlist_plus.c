/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 17:17:14 by aleduc            #+#    #+#             */
/*   Updated: 2019/04/08 15:58:55 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void		ddelmul(t_multi **head, t_multi *del)
{
	if (*head == NULL || del == NULL)
		return ;
	if (*head == del)
		*head = del->next;
	if (del->next != NULL)
		del->next->prev = del->prev;
	if (del->prev != NULL)
		del->prev->next = del->next;
	free(del->input);
	free(del);
	return ;
}

void		multi_push(t_multi **head)
{
	t_multi	*new_node;

	new_node = (t_multi*)malloc(sizeof(t_multi));
	new_node->next = (*head);
	new_node->prev = NULL;
	if ((*head) != NULL)
		(*head)->prev = new_node;
	(*head) = new_node;
}

void	reset_stop(char **inputstr, t_pos *pos, t_integrity *count)
{
	if (pos->stop == 1)
	{
		count->quote = 0;
		count->dquote = 0;
		pos->stop = 0;
		ft_strdel(inputstr);
	}
}
