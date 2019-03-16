/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textselection.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 17:19:37 by aleduc            #+#    #+#             */
/*   Updated: 2019/03/16 04:05:46 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

t_node *paste_clipboard(t_node **input, t_node *lstcursor, t_pos *pos)
{
    int i;

    i = 0;
    if(pos->selection == 1)
    {
        lstcursor = delete_selection(input, lstcursor, pos);
        redraw(pos, lstcursor);
        pos->selection = 0;
    }
    while(pos->clipboard[i])
    {
        insert(lstcursor, pos->clipboard[i]);
        ft_putchar(pos->clipboard[i]);
        i++;
    }
    lstcursor = find_tail(lstcursor, pos);
    return (lstcursor);
}

void        copy_selection(t_node *lstcursor, t_pos *pos)
{
    t_node *cursorcpy;
    int i;
    int count;
    
    if(pos->clipboard != NULL)
        free(pos->clipboard);
    pos->clipboard = (char *)malloc(sizeof(char) * 2048);
    cursorcpy = lstcursor;
    count = pos->selectcount;
    i = 0;
    
    if(count < 0)
    {
        while(count <= -1)
        {
            pos->clipboard[i] = cursorcpy->key;
            i++;
            count++;
            cursorcpy = cursorcpy->prev;
        }
        pos->clipboard[i] = '\0';
    }
    if(count > 0)
    {
        while(count >= 0)
        {
            pos->clipboard[i] = cursorcpy->key;
            i++;  
            count--;
            cursorcpy = cursorcpy->next;
        }
        pos->clipboard[i] = '\0';
        reverse_str(pos->clipboard);
        
    }
}

t_node      *undo_selection(t_node *lstcursor, t_pos *pos)
{
    t_node *cursorcpy;

    cursorcpy = lstcursor;
    savecursor(pos);
    ft_putstr(tgetstr("ei", NULL));
    if(pos->selectcount < 0)
    {
        while(pos->selectcount <= 0)
        {
            stalk_cursor(pos);
            ft_putchar(cursorcpy->key);
            if(pos->column == pos->termsize.ws_col)
                go_downleft(pos);
            cursorcpy = cursorcpy->prev;
            pos->selectcount++;
        }
        pos->selectcount = 0;
    }
    
    if(pos->selectcount > 0)
    {
        while(pos->selectcount > 0)
        {
            stalk_cursor(pos);
            if(pos->column != 1)
                ft_putstr(tgetstr("le", NULL));
            if(pos->column == 1)
                go_upright(pos);
            cursorcpy = cursorcpy->next;
            pos->selectcount--;
        }
        while (cursorcpy->prev != NULL)
        {
            ft_putchar(cursorcpy->key);
            cursorcpy = cursorcpy->prev;
        }
        pos->selectcount = 0;
    }
    
    ft_putstr(tgetstr("im", NULL));
    pos->selection = 0;
    cursorback(pos);
    return(lstcursor);
}

t_node      *find_tail(t_node *lstcursor, t_pos *pos)
{
    int backup;

    backup = 0;
    savecursor(pos);
    while(lstcursor->prev != NULL)
    {
        stalk_cursor(pos);
        if(pos->column != pos->termsize.ws_col)
            ft_putstr(tgetstr("nd", NULL));
        else
            go_downleft(pos);
        backup++;
        lstcursor = lstcursor->prev;
    }
    while(backup-- > 1)
        lstcursor = lstcursor->next;
    stalk_cursor(pos);
    pos->tailcolumn = pos->column;
    pos->tailrow = pos->row;
    cursorback(pos);
    return (lstcursor);
}

t_node      *delete_selection(t_node **input, t_node *lstcursor, t_pos *pos)
{
    stalk_cursor(pos);
    ft_putstr(tgetstr("ei", NULL));
    if(pos->selectcount > 0)
    {
        while(pos->selectcount > 0)
        {
            stalk_cursor(pos);
            if(pos->column == 1)
                go_upright(pos);
            else
                ft_putstr(tgetstr("le", NULL));
            ft_putstr(tgetstr("cd", NULL));
            if(lstcursor->next)
                ddel(input, lstcursor->next);
            pos->selectcount--;
        }
        if(lstcursor->prev != NULL)
            lstcursor = lstcursor->next;
        pos->selectcount = 0;
    }
    if(pos->selectcount < 0)
    {
        while(pos->selectcount < 0)
        {
            stalk_cursor(pos);
            ft_putstr(tgetstr("cd", NULL));
            if(pos->column == pos->termsize.ws_col)
                go_downleft(pos);
            lstcursor = lstcursor->prev;
            ddel(input, lstcursor->next);
            pos->selectcount++;
        }
        if(lstcursor->next != NULL)
            lstcursor = lstcursor->next;
        pos->selectcount = 0;
    }
    ft_putstr(tgetstr("im", NULL));
    pos->selection = 0;
    lstcursor = find_tail(lstcursor, pos);
    return(lstcursor);
}

t_node      *anchor_selection(t_node *lstcursor, t_pos *pos, int direction)
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

t_node      *selectmode(t_node **input, t_node *lstcursor, char buffer[], t_pos *pos)
{
    if(SHIFT_LEFT || SHIFT_RIGHT)
    {
        if (pos->selection == 0)
            pos->selection = 1;
        if(pos->selectcount >= 0 && SHIFT_RIGHT)
            lstcursor = shift_right(lstcursor, buffer, pos);
        if(pos->selectcount < 0 && SHIFT_RIGHT)
            lstcursor = anchor_selection(lstcursor, pos, 0);
        if(pos->selectcount <= 0 && SHIFT_LEFT)
            lstcursor = shift_left(lstcursor, buffer, pos);
        if(pos->selectcount > 0 && SHIFT_LEFT)
            lstcursor = anchor_selection(lstcursor, pos, 1);
    }
    if((ALT_C || ALT_X) && pos->selection == 1)
        copy_selection(lstcursor, pos);
    if(ALT_X && pos->selection == 1)
    {
        lstcursor = delete_selection(input, lstcursor, pos);
        redraw(pos, lstcursor);
    }
    if(ALT_V)
        lstcursor = paste_clipboard(input, lstcursor, pos);
    if(!SHIFT_LEFT && !SHIFT_RIGHT  && !ALT_C && !ALT_X  && !ALT_V && pos->selection == 1) // && COPY && CUT)
        lstcursor = undo_selection(lstcursor, pos);
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
                ft_putchar(lstcursor->key);
                lstcursor = lstcursor->prev;
                go_downleft(pos);
            }
            ft_putstr(tgetstr("me", NULL));
            ft_putstr(tgetstr("im", NULL));
        }
    }
    return(lstcursor);
}
