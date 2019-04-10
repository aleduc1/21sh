/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 17:18:13 by aleduc            #+#    #+#             */
/*   Updated: 2019/04/08 16:44:28 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

char	*ft_strdup_history(const char *s1)
{
	size_t	i;
	char	*dest;

	i = 0;
	while (s1[i])
		i++;
	if (!(dest = (char*)malloc(sizeof(*s1) * (i + 1))))
		return (NULL);
	i = 0;
	while (s1[i])
	{
        if(s1[i] == '\n')
            dest[i] = ' ';
        else
		    dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void        inserthistory(t_node *prev_node, char *line, t_pos *pos)  
{  
    t_node* new_node;
    int something;
    int i;
    
    i = -1;
    something = 0;
    while (line[++i])
        if (line[i] != ' ' || line[i] != '\t')
            something = 1;
    if (something != 1)
        return ;
    if (prev_node == NULL)
        return ;  
    new_node = (t_node*)malloc(sizeof(t_node));
    new_node->line = ft_strdup_history(line);
    pos->historysum++;
    new_node->next = prev_node->next;
    prev_node->next = new_node;
    new_node->prev = prev_node;
    if (new_node->next != NULL)  
        new_node->next->prev = new_node;
      
}

t_node      *history_downcase(t_node *lstcursor, t_node **input, t_pos *pos) //keeping for later
{
    clean_for_history(lstcursor, input, pos);
    while ((*input)->next != NULL)
        ddel(input, *input);
    dpush(input, ' ');
    lstcursor = *input;
    pos->historycount = 1;
    return (lstcursor);
}

t_node      *clean_for_history(t_node *lstcursor, t_node **input, t_pos *pos)
{
    tputs(tgoto(tgetstr("cm", NULL), pos->tailcolumn - 1, pos->tailrow - 1), 1, ft_outc);
    lstcursor = *input;
    while (lstcursor->next != NULL)
    {
        stalk_cursor(pos);
        if (pos->column == 1)
            go_upright(pos);
        else
            ft_putstr(tgetstr("le", NULL));
        ft_putstr(tgetstr("cd", NULL));
        lstcursor = lstcursor->next;
        stalk_cursor(pos);
    }
    return (lstcursor);
}

t_node      *history_to_lst(t_node *lstcursor, char *historyline, t_node **input, t_pos *pos)
{
    int     i;

    i = -1;
    stalk_cursor(pos);
    while ((*input)->next != NULL)
        ddel(input, *input);
    while (historyline[++i])
        insert(*input, historyline[i]);
    dprintlist(*input, 0);
    ft_putstr(tgetstr("le", NULL));
    ft_putstr(tgetstr("cd", NULL));
    stalk_cursor(pos);
    pos->tailcolumn = pos->column;
    pos->tailrow = pos->row;
    lstcursor = *input;
    return (lstcursor);
}
