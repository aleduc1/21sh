/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textselection.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 17:19:37 by aleduc            #+#    #+#             */
/*   Updated: 2019/03/12 21:23:20 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

t_node      *selectmode(char buffer[], t_pos *pos)
{
    if(SHIFT_LEFT || SHIFT_RIGHT)
    {
        if (pos->selection == 0)
            pos->selection = 1;
    }
    return (0);
}

t_node      *shift_left(t_node *lstcursor, char buffer[], t_pos *pos)
{
    if (SHIFT_LEFT)
    {
        if(lstcursor->next)
        {
            ft_putstr(tgetstr("ei", NULL));
            ft_putstr(tgetstr("mr", NULL));
            if(pos->column != 1)
            {   
                ft_putstr(tgetstr("le", NULL));
                ft_putchar(lstcursor->next->key);
                insert(pos->clipboard, lstcursor->next->key);
                lstcursor = lstcursor->next;
                ft_putstr(tgetstr("le", NULL));
            } 
            if(pos->column == 1)
            {
                go_upright(pos);
                ft_putchar(lstcursor->next->key);
                insert(pos->clipboard, lstcursor->next->key);
                lstcursor = lstcursor->next;
            }
            ft_putstr(tgetstr("me", NULL));
            ft_putstr(tgetstr("im", NULL));
        }
    }
    return(lstcursor);
}

t_node      *shift_right(t_node *lstcursor, char buffer[], t_pos *pos)
{
    if (SHIFT_RIGHT)
    {
        if(lstcursor->prev)
        {
            ft_putstr(tgetstr("ei", NULL));
            ft_putstr(tgetstr("mr", NULL));
            if(pos->column != pos->termsize.ws_col)
            {   
                ft_putchar(lstcursor->key);
                insert(pos->clipboard, lstcursor->key);
                lstcursor = lstcursor->prev;
            } 
            if(pos->column == pos->termsize.ws_col)
            {
                go_downleft(pos);
                ft_putchar(lstcursor->prev->key);
                insert(pos->clipboard, lstcursor->prev->key);
                lstcursor = lstcursor->prev;
            }
            ft_putstr(tgetstr("me", NULL));
            ft_putstr(tgetstr("im", NULL));
        }
    }
    return(lstcursor);
}
