/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 10:31:02 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/20 12:17:57 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int		modify_dst(char *src, char **dst)
{
	char	*stock;
	char	*final;

	stock = manage_var(src);
	ft_strdel(&src);
	final = ft_strjoin(*dst, stock);
	ft_strdel(&(*dst));
	if (final)
		(*dst) = final;
	ft_strdel(&stock);
	return (0);
}

char	*manage_var(char *str)
{
	char	*final;

	if (ft_strequ(str, "$"))
		final = ft_itoa(getpid());
	else
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
