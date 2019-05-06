/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arraydel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 22:17:10 by sbelondr          #+#    #+#             */
/*   Updated: 2019/04/08 09:52:15 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void		ft_arraydel(char ***line)
{
	int	i;

	i = -1;
	if (*line)
	{
		while ((*line)[++i])
			ft_strdel(&((*line)[i]));
		free(*line);
		*line = NULL;
	}
}
