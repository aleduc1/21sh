#include "21s.h"

t_node      *up(t_node *lstcursor, t_node **input, char buffer[], t_pos *pos)
{
    t_node *cursorhis;
    int i;
    
    cursorhis = pos->history;
    if(ARROW_UP)
    {
        i = 1;
        if(pos->historycount < pos->historysum)
        {
            clean_for_history(lstcursor, input, pos);
            pos->historycount++;
            while(i <= pos->historycount)
            {
                if(!(cursorhis->next))
                    break ;
                cursorhis = cursorhis->next;
                i++;
            }
            lstcursor = history_to_lst(lstcursor, cursorhis->line, input, pos);
        }
    }
    return(lstcursor);
}

t_node      *down(t_node *lstcursor, t_node **input, char buffer[], t_pos *pos)
{
    t_node *cursorhis;
    int i;
    
    cursorhis = pos->history;
    if(ARROW_DOWN)
    {
        i = -1;
        if(pos->historycount > 1)
        {  
            clean_for_history(lstcursor, input, pos);
            pos->historycount--;
            while(++i < pos->historycount)
            {
                if(!(cursorhis->next))
                    break ;
                cursorhis = cursorhis->next;
            }
            lstcursor = history_to_lst(lstcursor, cursorhis->line, input, pos);
        }
    }
    return (lstcursor);
}

t_node      *left(t_node *lstcursor, char buffer[], t_pos *pos)
{
    if (ARROW_LEFT)
    {
        if(lstcursor->next)
        {
            if(pos->column == 1)
            {
                lstcursor = lstcursor->next;
                pos->currentline--;
                go_upright(pos);
            }
            else
            {
                ft_putstr(tgetstr("le", NULL));
                lstcursor = lstcursor->next;
                stalk_cursor(pos);
            }
        }
    }
    return (lstcursor);
}

t_node      *right(t_node *lstcursor, char buffer[], t_pos *pos)
{
    if (ARROW_RIGHT)
    {
        if(lstcursor->prev)
        {
            if(pos->column == pos->termsize.ws_col)
            {
                lstcursor = lstcursor->prev;
                pos->currentline++;
                go_downleft(pos);
            }
            else
            {
                ft_putstr(tgetstr("nd", NULL));
                stalk_cursor(pos);
                lstcursor = lstcursor->prev;
            }
        }
    }
    return(lstcursor);
}

t_node      *backspace(t_node *lstcursor, t_node **input, char buffer[], t_pos *pos)
{
    if (BACKSPACE)
    {
        if (lstcursor->next)
        {
            if(pos->column == 1)
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
                if(lstcursor->next)
                    redraw(pos, lstcursor);
            }
        }
    }
    return (lstcursor);
}

t_node      *del_key(t_node *lstcursor, t_node **input, char buffer[], t_pos *pos)
{
    if (DELETE)
    {
        if (lstcursor->prev)
        {
            ft_putstr(tgetstr("dc", NULL));
            if(pos->tailcolumn == 1)
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
    }
    return(lstcursor);
}

t_node      *ctrl_n_friends(t_node *lstcursor, char buffer[])
{
    if (CTRL_D)
    {
        ft_putstr(tgetstr("ei", NULL));
        default_term_mode();
            exit(1);
    }
    return (lstcursor);
}


// if (SHIFT_UP)
//     {
//         ft_putstr(" [");
//         ft_putnbr(pos->row);
//         ft_putstr("/");
//         ft_putnbr(pos->termsize.ws_row);
//         ft_putchar('|');
//         ft_putnbr(pos->column);
//         ft_putstr("/");
//         ft_putnbr(pos->termsize.ws_col);
//         ft_putstr("]");
//         // ft_putchar('{');
//         // ft_putnbr(pos->currentline+1);
//         // ft_putchar('/');
//         // ft_putnbr(pos->nblines+1);
//         // ft_putchar('}');
//         // ft_putchar('[');
//         // ft_putnbr(pos->startrow);
//         // ft_putchar('|');
//         // ft_putnbr(pos->startcolumn);
//         // ft_putchar(']');
//         // ft_putchar('(');
//         // ft_putnbr(pos->inputlen);
//         // ft_putchar(')');
//         // //ft_putstr(tgetstr("ce", NULL));
//         // //stalk_cursor(pos);

//         ft_putstr("(");
//         ft_putnbr(pos->tailrow);
//         ft_putchar('|');
//         ft_putnbr(pos->tailcolumn);
//         ft_putchar(')');
//     }