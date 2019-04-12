#include "sh21.h"

void    reset_multi(t_pos *pos)
{
    stalk_cursor(pos);
    pos->tailcolumn = pos->column;
    pos->tailrow = pos->tailrow;
    pos->selection = 0;
    pos->selectcount = 0;
    pos->inputlen = 0;
    get_startingpos(pos);
}

t_node *try_to_match(t_node *cursor, t_integrity *count, char type)
{
    t_node *cursorcpy;
    
    cursorcpy = cursor;
    cursor = cursor->prev;
    while(cursor->prev)
    {
        if(cursor->key == type)
        {
            if(type == '"')
                count->dquote++;
            if(type == '\'')
                count->quote++;
            return(cursor->prev);
        }
        cursor = cursor->prev;
    }
    return(cursorcpy);
}

void key_occurence(t_node *cursor, t_integrity *count)
{
    while (cursor)
    {
        if(cursor->key == '"' && (count->quote % 2) == 0)
        {
            count->dquote++;
            cursor = try_to_match(cursor, count, '"');
        }
        if (cursor->key == '\'' && (count->dquote % 2) == 0)
        {
            count->quote++;
            cursor = try_to_match(cursor, count, '\'');
        }
        cursor = cursor->prev;
    }
}

int check_integrity(t_node *input, t_multi **multi, t_pos *pos, t_integrity *count)
{
    t_multi *lstcursor;
    t_node *cursor;

    cursor = input;
    while(cursor->next != NULL)
        cursor = cursor->next;
    key_occurence(cursor, count);
    if((count->dquote % 2) != 0)
    {
        lstcursor = *multi;
        multi_push(multi);
        lstcursor = lstcursor->prev;
        lstcursor->input = NULL;
        dpush(&lstcursor->input, ' ');
        ft_putstr("dquote>");
        read_input(&lstcursor->input, pos);
        return (-1);
    }
    if ((count->quote % 2) != 0)
    {
        lstcursor = *multi;
        multi_push(multi);
        lstcursor = lstcursor->prev;
        lstcursor->input = NULL;
        dpush(&lstcursor->input, ' ');
        ft_putstr("quote>");
        read_input(&lstcursor->input, pos);
        return (-1);
    }
    return (1);
}