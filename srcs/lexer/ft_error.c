/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 16:28:46 by aleduc            #+#    #+#             */
/*   Updated: 2019/05/07 18:47:22 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	ft_error(int code_error)
{
	if (code_error == 0)
		ft_putendl("It appears you made a grammatical mistake, plz type the\
				command again following the grammar rules of our shell.\n \
				Type 'Usage' for more info.");
}
