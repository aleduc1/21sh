/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 17:49:15 by aleduc            #+#    #+#             */
/*   Updated: 2019/04/03 18:43:39 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
** Goal : 
** Link every token word into only one
** Erase other token
** Set token's type to be CMD
** Set token's data to "cmd"
** set token's cmd field as the char ** containing the command and it arguments
** 
** Coding :
** Go through LL.
** When operator is met : do the link if needed
** It is needed if : before the operator there is mutliple token word next to each other
**
** One way of doing it :
** Increase an int everytime we meet a word token
** Reset it to 0 otherwise
** When we meet a operator token
** If the int is > 1 do the link
**
** Another way of doing it :
** When we meet an operator token, if the two token before are word
** Do the link, just sending the linked list and the operator node to the link function
** 
** Advantage of option 1 is that i already know the start and end node position
** Advantage of option 2 is that it's probably faster and more straight-forward
**
** Use option 2 and add a function to find the first word in the streak before before sending it to link
**
** Link will require the first word token encountered and the last before the operator
** To link I could :
** Create a new token and place it on the LL (opt1)
** Modify the first token and remove the other (opt2)
** Option 2 is easier and faster so I'll use it.
** 
*/
