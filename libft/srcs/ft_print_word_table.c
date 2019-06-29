/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_word_table.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 14:47:55 by aleduc            #+#    #+#             */
/*   Updated: 2017/11/13 14:56:27 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_word_table(char **words)
{
	if (words == NULL)
		return ;
	while (*words)
		ft_putendl(*words++);
}
