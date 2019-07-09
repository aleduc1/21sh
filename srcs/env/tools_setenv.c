/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_setenv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 14:54:24 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/28 11:18:42 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void		setenv_error(void)
{
	ft_dprintf(STDERR_FILENO, "21sh: setenv: Variable name ");
	ft_dprintf(STDERR_FILENO, "must contain alphanumeric characters.\n");
}

int			is_correct_setenv(char c)
{
	if (ft_isalnum(c) || c != '=')
		return (1);
	return (0);
}

int			str_is_alpha(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (is_correct_setenv(str[i]) == 0)
		{
			setenv_error();
			return (0);
		}
	return (1);
}
