#include "21s.h"

t_node      *check_input(t_node *lstcursor, t_node **input, char buffer[], t_pos *pos)
{
    lstcursor = left(lstcursor, buffer, pos);
    lstcursor = right(lstcursor, buffer, pos);
    lstcursor = up(lstcursor, input, buffer, pos);
    lstcursor = down(lstcursor, input, buffer, pos);
    lstcursor = backspace(lstcursor, input, buffer, pos);
    lstcursor = del_key(lstcursor, input, buffer, pos);
    lstcursor = ctrl_n_friends(lstcursor, buffer);
    lstcursor = backwardjump(lstcursor, buffer, pos);
    lstcursor = forwardjump(lstcursor, buffer, pos);
    lstcursor = home_end(lstcursor, buffer, pos);
    return (lstcursor);
}

void    wrapping(t_pos *pos)
{
    if (pos->tailrow == pos->termsize.ws_row && pos->tailcolumn == 0)
    {
        if(pos->tailrow != pos->startrow)
            pos->tailrow--;
        pos->nblines++;
        pos->currentline--;
        savecursor(pos);
        tputs(tgoto(tgetstr("cm", NULL), 0, pos->termsize.ws_row), 1, ft_outc);
        ft_putstr(tgetstr("sf", NULL));
        cursorback(pos);
        pos->row--;
        ft_putstr(tgetstr("up", NULL));
    }
}

void    redraw(t_pos *pos, t_node *lstcursor)
{
    t_node *cursorcpy;
    
    if(lstcursor->prev != NULL)
    {
        wrapping(pos);
        cursorcpy = lstcursor->next;
        savecursor(pos);
        while (cursorcpy->prev != NULL)
        {
            ft_putchar(cursorcpy->prev->key);
            cursorcpy = cursorcpy->prev;
        }
        tputs(tgoto(tgetstr("cm", NULL), pos->tailcolumn - 1, pos->tailrow - 1), 1, ft_outc);
        ft_putstr(tgetstr("ce", NULL));
        cursorback(pos);
    }
}

void actualize(t_pos *pos, t_node *lstcursor, t_node **input, char buffer[])
{
    stalk_cursor(pos);
    if (pos->column == pos->termsize.ws_col)
    {
        ft_putchar(buffer[0]);
        wrapping(pos);
        go_downleft(pos);
        pos->nblines++;
        pos->currentline++;
    }
    else
        ft_putchar(buffer[0]);
    get_tail(pos);
    redraw(pos, lstcursor);
    savecursor(pos);
    get_inputlen(pos, *input);
}

t_node      *editline(t_pos *pos, t_node *lstcursor, t_node **input, char buffer[])
{
    if(!PRINTABLE)
        lstcursor = check_input(lstcursor, input, buffer, pos);
    if(PRINTABLE && pos->selection == 0)
    {
        insert(lstcursor, buffer[0]);
        actualize(pos, lstcursor, input, buffer);
    }
    return(lstcursor);
}