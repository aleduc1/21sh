#include "21s.h"

t_node      *selectmode(char buffer[], t_pos *pos)
{
    if(SHIFT_DOWN)
    {
        if (pos->selection == 0)
        {
            pos->whichside = 0;
            pos->selection = 1;
        }
        else
        {
            pos->selection = 0;
        }
    }
    if(SHIFT_UP)
    {
        if(pos->clipboard)
        {
            ddellist(pos->clipboard);
            dpush(&pos->clipboard, ' ');
        }
    }
    return (0);
}

t_node      *shift_left(t_node *lstcursor, char buffer[], t_pos *pos)
{
    if (SHIFT_LEFT && (pos->whichside == 0 || pos->whichside == 1))
    {
        pos->whichside = 1;
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
    if (SHIFT_RIGHT && (pos->whichside == 0 || pos->whichside == 2))
    {
        pos->whichside = 2;
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