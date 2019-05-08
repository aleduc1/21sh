/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 10:31:02 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/08 16:27:26 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char	*manage_var(char *str)
{
	char	*final;

	final = value_line_path(str, 0);
	if (!final)
		final = ft_strdup("");
	return (final);
}

int		manage_home(char *src, char **dst, int index)
{
	char	*data;

	index += 1;
	if (src[index] == '-')
	{
		index++;
		data = manage_var("OLDPWD");
	}
	else if (src[index] == '+')
	{
		index++;
		data = manage_var("PWD");
	}
	else
		data = manage_var("HOME");
	ft_strdel(&(*dst));
	(*dst) = data;
	return (index);
}
