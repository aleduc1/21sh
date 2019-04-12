/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 17:49:15 by aleduc            #+#    #+#             */
/*   Updated: 2019/04/05 19:40:12 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
** 1- Identifying start and end of the part of the LL to detach
** 2- Detach it
** 3- Create a command token with the LL in it
** 4- Attach it to the LL
** 5- Move pointer for whats after the cmd token's node and repeat if its not finished
*/

/*
** Made a separate function to be able to use it for start and end
*/ 

int		IsOperator(t_type type)
{
	if (type == SPIPE || type == DPIPE || type == AMPERSAND || type == DAMPERSAND || type == SCOLON || type == DSCOLON)
		return (1);
	return (0);
}

/*
** We want to end on the node of one of those type
*/

int		TypeToEndOn(t_type type)
{
	if (IsOperator(type) || type == DELIM)
		return (0);
	return (1);
}

/*
** We want to start on the node after those type
*/

int		TypeToIgnore(t_type	type)
{
	if (IsOperator(type) || type == DELIM/*|| type == COMMAND*/)
		return (1);
	return (0);
}

void	set_end(t_lex **end)
{
	while (*end && TypeToEndOn((*end)->token->type))
		*end = (*end)->next;
}

void	set_start(t_lex **start)
{
	while (*start && TypeToIgnore((*start)->token->type))
		*start = (*start)->next;
}

void	IdentifyDelim(t_lex **start, t_lex **end)
{
	set_start(start);
	*end = *start;
	set_end(end);
}

void	SetDelim(t_lex **head, t_lex **start, t_lex **end)
{
	*start = *head;
	*end = *head;
}

void	pre_parsing(t_lex **head)
{
	t_lex	*start;
	t_lex	*end;
	t_token	*command;

	while () // Unsure about this part yet
	{
		// Assign start and end pointer at head
		SetDelim(head, &start, &end); // Done

		// Set start on the first node we want, and end after the last node we want
		IdentifyDelim(&start, &end); // Done and tested

		// Detach the DLL to make it unrelated to the whole lexer, ending with a NULL ptr
		Detach(&start, &end); // Thats what i need to do

		// Create a command token with the standalone DLL inside (maybe make token->data to be a void* to be able to cast char* or LL)
		command = CreateCommandToken(*head, delim); // Not done yet

		// Create the node and link it to the Lexer DLL
		LinkCommandToLexer(*head, &command, delim); // Not done yet

		// Unsure about this part yet
		loop = SetPtrPos(head); // Condition of the loop/Moving ptr after Operator if needed/not Empty

		// Reseting command token pointer, wich mean it must be duplicated when creating a node with token command inside, not assigned
		ft_memdel((void **)&command); 
	}
}
