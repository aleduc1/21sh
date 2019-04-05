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
** Goal :
** Regroup tokens into simple commands
** Create a token command for simple commands
** In it we will put every token between operator, so a LL
** 
** Coding :
** From the last cut point to the new one, we need to split this part of the LL
** And put it into a simple command token
** Once part of the LL is detached , connect it to a simple command token's node
** 
** Steps :
** 1- Identifying start and end of the part of the LL to detach
** 		Can be broken down into 2 step
** 2- Detach it
** 3- Create a command token with the LL in it
** 4- Attach it to the LL
** 5- Move pointer for whats after the cmd token's node and repeat if its not finished
**
** Breakdown :
** 1:
** - if token delim go on step after
** - if LL is still existant
** - set start as where i am
*/


