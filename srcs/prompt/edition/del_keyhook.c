/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stalkcursor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 17:19:17 by aleduc            #+#    #+#             */
/*   Updated: 2019/04/17 15:24:00 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

t_node	*backspace(t_node *lstcursor, t_node **input, char buffer[], t_pos *pos)
{
	if (BACKSPACE && lstcursor->next)
	{
		if (pos->column == 1)
		{
			go_upright(pos);
			ft_putstr(tgetstr("dc", NULL));
			pos->tailcolumn = 0;
			ddel(input, lstcursor->next);
		}
		else
		{
			pos->tailcolumn--;
			ft_putstr(tgetstr("le", NULL));
			ft_putstr(tgetstr("dc", NULL));
			ddel(input, lstcursor->next);
			if (lstcursor->next)
				redraw(pos, lstcursor);
		}
	}
	return (lstcursor);
}

t_node	*del_key(t_node *lstcursor, t_node **input, char buffer[], t_pos *pos)
{
	if (DELETE && lstcursor->prev)
	{
		ft_putstr(tgetstr("dc", NULL));
		if (pos->tailcolumn == 1)
		{
			pos->tailcolumn = pos->termsize.ws_col;
			pos->tailrow--;
		}
		else
			pos->tailcolumn--;
		lstcursor = lstcursor->prev;
		ddel(input, lstcursor->next);
		redraw(pos, lstcursor);
	}
	return (lstcursor);
}
