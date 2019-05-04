/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 17:13:21 by aleduc            #+#    #+#             */
/*   Updated: 2019/05/04 22:03:25 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void			init_prompt(t_pos *pos)
{
	raw_term_mode();
	pos->history = NULL;
	dpush(&pos->history, 'X');
	pos->clipboard = NULL;
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
	pos->stop = 0;
}

int				check_integrity(t_node *input, t_multi **multi, t_pos *pos,\
													t_integrity *count)
{
	t_node		*cursor;
	t_multi		*lstcursor;

	cursor = input;
	lstcursor = NULL;
	while (cursor->next != NULL)
		cursor = cursor->next;
	key_occurence(cursor, count);
	if ((count->dquote % 2) != 0)
	{
		dquote(lstcursor, multi, pos);
		return (-1);
	}
	if ((count->quote % 2) != 0)
	{
		quote(lstcursor, multi, pos);
		return (-1);
	}
	return (1);
}

t_node			*read_input(t_node **input, t_pos *pos)
{
	char		buffer[1000];
	t_node		*lstcursor;

	lstcursor = *input;
	reset_multi(pos);
	ft_bzero(buffer, 1000);
	ft_putstr(tgetstr("im", NULL));
	while (read(STDIN_FILENO, &buffer, 1000) > 0 && !ENTER)
	{
		lstcursor = editline(pos, lstcursor, input, buffer);
		//printf("%c('%d') | %c('%d') | %c('%d') | %c('%d')\n", buffer[0], buffer[0],buffer[1],buffer[1],buffer[2],buffer[2],buffer[3], buffer[3]);
		stalk_cursor(pos);
		ft_bzero(buffer, 1000);
		if (pos->stop == 1)
		{
			pos->stop = 0;
			return (*input);
		}
	}
	travel_to_last(lstcursor, pos);
	ft_putstr("\n");
	return (*input);
}

char			*prompt(t_multi *multi, t_pos *pos) //NORME
{
	t_integrity	count;
	t_multi		*lstcursor;
	char		*inputstr;

	multi = NULL;
	inputstr = NULL;
	print_prompt();
	multi_push(&multi);
	multi->input = NULL;
	dpush(&multi->input, ' ');
	multi->input = read_input(&multi->input, pos);
	lstcursor = multi;
	if (multi->input)
	{
		count.dquote = 0;
		count.quote = 0;
		while (check_integrity(lstcursor->input, &multi, pos, &count) < 0)
			lstcursor = lstcursor->prev;
		lstcursor = multi;
		inputstr = lst_to_str(&multi, inputstr);
		inserthistory(pos->history, inputstr, pos);
	}
	ft_putstr("Input : ");
	ft_putendl(inputstr);
	ft_putstr("Clipboard : ");
	ft_putendl(pos->clipboard);
	ddellist(multi);
	pos->historycount = 0;
	return (inputstr);
}
