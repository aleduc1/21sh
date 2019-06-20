/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_selection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 00:32:02 by mbellaic          #+#    #+#             */
/*   Updated: 2019/06/18 23:06:20 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void		ddel_select(t_node **head, t_node *del)
{
	if (*head == NULL || del == NULL)
		return ;
	if (*head == del)
		*head = del->prev;
	if (del->next != NULL)
		del->next->prev = del->prev;
	if (del->prev != NULL)
		del->prev->next = del->next;
	free(del);
	return ;
}

t_node		*delete_selection_left(t_node **input, t_node *lstcursor,
															t_pos *pos)
{
	while (pos->selectcount > 0)
	{
		stalk_cursor(pos);
		if (pos->column == 1)
			go_upright(pos);
		else
			ft_putstr(tgetstr("le", NULL));
		ft_putstr(tgetstr("dc", NULL));
		if (lstcursor->next)
			ddel_select(input, lstcursor->next);
		pos->selectcount--;
	}
	if (lstcursor->prev && lstcursor->next)
		lstcursor = lstcursor->next;
	pos->selectcount = 0;
	return (lstcursor);
}

t_node		*delete_selection_right(t_node **input, t_node *lstcursor,
															t_pos *pos)
{
	while (pos->selectcount < 0)
	{
		stalk_cursor(pos);
		ft_putstr(tgetstr("dc", NULL));
		if (pos->column == pos->termsize.ws_col)
			go_downleft(pos);
		lstcursor = lstcursor->prev;
		ddel_select(input, lstcursor->next);
		pos->selectcount++;
	}
	pos->selectcount = 0;
	return (lstcursor);
}

t_node		*delete_selection(t_node **input, t_node *lstcursor, t_pos *pos)
{
	stalk_cursor(pos);
	if (pos->selectcount > 0)
		lstcursor = delete_selection_left(input, lstcursor, pos);
	if (pos->selectcount < 0)
		lstcursor = delete_selection_right(input, lstcursor, pos);
	find_tail(lstcursor, pos);
	pos->selection = 0;
	return (lstcursor);
}
