/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stalkcursor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 17:19:17 by aleduc            #+#    #+#             */
/*   Updated: 2019/04/01 14:50:20 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void    get_cursor(int i, int j, char answer[], t_pos *pos) //extra 1 line.
{
    char xchar[5];
    char ychar[5];
    
    while(answer[++i] != ';')
    {
        if((answer[i] >= '0' && answer[i] <= '9'))
        {
            xchar[j] = answer[i];
            j++;
        }
    }
    xchar[j] = '\0';
    j = 0;
    while(answer[++i] != 'R')
    {
        if((answer[i] >= '0' && answer[i] <= '9'))
        {
            ychar[j] = answer[i];
            j++;
        }
    }
    ychar[j] = '\0';
    pos->row = ft_atoi(xchar);
    pos->column = ft_atoi(ychar);
}

void       stalk_cursor(t_pos *pos)
{
    char answer[16];
    size_t answerlen;
    int i = 1;
    int j = 0;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &pos->termsize);
    write(0, "\x1B[6n", 5); 
    answerlen = 0;
    while (answerlen < sizeof(answer) - 1 && 
            read(STDIN_FILENO, answer + answerlen, 1) == 1)
    {
        if (answer[answerlen ++] == 'R') 
            break;
    }
    answer[answerlen] = '\0';
    get_cursor(i, j, answer, pos);
    
}

void    get_tail(t_pos *pos)
{
    if(pos->tailcolumn < pos->termsize.ws_col)
        pos->tailcolumn++;
    if(pos->tailcolumn == pos->termsize.ws_col)
    {
        pos->tailcolumn = 0;
        if(pos->tailrow < pos->termsize.ws_row)
            pos->tailrow++;
    }
    if(pos->tailrow >= pos->termsize.ws_row)
        pos->tailrow = pos->termsize.ws_row;
}

void        savecursor(t_pos *pos)
{
    stalk_cursor(pos);
    pos->savecolumn = pos->column;
    pos->saverow =  pos->row;
}

void        cursorback(t_pos *pos)
{
    tputs(tgoto(tgetstr("cm", NULL), pos->savecolumn - 1, pos->saverow - 1), 1, ft_outc);
}
