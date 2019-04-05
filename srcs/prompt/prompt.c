/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 17:13:21 by aleduc            #+#    #+#             */
/*   Updated: 2019/04/05 15:10:37 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	init_prompt(t_pos *pos)
{
   //raw_term_mode();
    pos->history = NULL;
    dpush(&pos->history, 'X');
    pos->historycount = 0;
    pos->historysum = 0;
    pos->nblines = 0;
    pos->currentline = 0;
    pos->selection = 0;
    pos->selectcount = 0;
    pos->inputlen = 0;
    pos->savecolumn = 0;
    pos->saverow = 0;
    pos->startrow = 0;
    pos->startcolumn = 0;
    pos->tailcolumn = 0;
    pos->tailrow = 0;
}

t_node	*read_input(t_node **input, t_pos *pos)
{
    char buffer[6];
    t_node *lstcursor;
    
    lstcursor = *input;
    ft_bzero(buffer, 6);
    ft_putstr(tgetstr("im", NULL));
    while(read(STDIN_FILENO, &buffer, 6) > 0 && !ENTER)
    {
        lstcursor = editline(pos, lstcursor, input, buffer);
        //printf("%c('%d') | %c('%d') | %c('%d') | %c('%d')\n", buffer[0], buffer[0],buffer[1],buffer[1],buffer[2],buffer[2],buffer[3], buffer[3]);
        stalk_cursor(pos);
        ft_bzero(buffer,5);
    }
    travel_to_last(lstcursor, pos);
    ft_putstr("\n");
    
    return (*input);
}

char	*prompt(t_node *input, t_pos *pos)
{
    char *inputstr;

    raw_term_mode();
    print_prompt();
    get_startingpos(pos);
    inputstr = NULL;
    input = NULL;
    dpush(&input, ' ');
    input = read_input(&input, pos);
    if (input)
    {
        inputstr = lst_to_str(&input, inputstr);
        inserthistory(pos->history, inputstr, pos);
    }
    ft_putstr("Clipboard : ");
    ft_putendl(pos->clipboard);
    ddellist(input);
    pos->historycount = 0;
    default_term_mode();
    return (inputstr);
}
