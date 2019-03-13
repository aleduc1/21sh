/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textselection.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 17:19:37 by aleduc            #+#    #+#             */
/*   Updated: 2019/03/13 03:47:35 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

t_node      *unselect(t_node *lstcursor, t_pos *pos, int direction)
{
    ft_putstr(tgetstr("ei", NULL));
    if(direction == 0 && lstcursor->prev)
    {
        pos->selectcount++;
        ft_putchar(lstcursor->key);
        lstcursor = lstcursor->prev;
    }
    if(direction == 1 && lstcursor->next)
    {
        pos->selectcount--;
        ft_putstr(tgetstr("le", NULL));
        ft_putchar(lstcursor->next->key);
        lstcursor = lstcursor->next;
        ft_putstr(tgetstr("le", NULL));
    }
    ft_putstr(tgetstr("im", NULL));
    return(lstcursor);
}

t_node      *selectmode(t_node *lstcursor, char buffer[], t_pos *pos)
{
    if(SHIFT_LEFT || SHIFT_RIGHT)
    {
        if (pos->selection == 0)
            pos->selection = 1;
        if(pos->selectcount >= 0 && SHIFT_RIGHT)
            lstcursor = shift_right(lstcursor, buffer, pos);
        if(pos->selectcount < 0 && SHIFT_RIGHT)
            lstcursor = unselect(lstcursor, pos, 0);
        if(pos->selectcount <= 0 && SHIFT_LEFT)
            lstcursor = shift_left(lstcursor, buffer, pos);
        if(pos->selectcount > 0 && SHIFT_LEFT)
            lstcursor = unselect(lstcursor, pos, 1);
    }
    return (lstcursor);
}

t_node      *shift_left(t_node *lstcursor, char buffer[], t_pos *pos)
{
    if (SHIFT_LEFT)
    {
        if(lstcursor->next)
        {
            pos->selectcount--;
            ft_putstr(tgetstr("ei", NULL));
            ft_putstr(tgetstr("mr", NULL));
            if(pos->column != 1)
            {   
                ft_putstr(tgetstr("le", NULL));
                ft_putchar(lstcursor->next->key);
                lstcursor = lstcursor->next;
                ft_putstr(tgetstr("le", NULL));
            } 
            if(pos->column == 1)
            {
                go_upright(pos);
                ft_putchar(lstcursor->next->key);
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
            pos->selectcount++;
            ft_putstr(tgetstr("ei", NULL));
            ft_putstr(tgetstr("mr", NULL));
            if(pos->column != pos->termsize.ws_col)
            {   
                ft_putchar(lstcursor->key);
                lstcursor = lstcursor->prev;
            } 
            if(pos->column == pos->termsize.ws_col)
            {
                go_downleft(pos);
                ft_putchar(lstcursor->prev->key);
                lstcursor = lstcursor->prev;
            }
            ft_putstr(tgetstr("me", NULL));
            ft_putstr(tgetstr("im", NULL));
        }
    }
    return(lstcursor);
}
