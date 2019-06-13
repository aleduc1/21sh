/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 17:57:48 by sbelondr          #+#    #+#             */
/*   Updated: 2019/06/02 18:24:02 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/*
** split is all the path
*/

static int	path_of_commands(char ***command, char **split)
{
	int		i;
	char	*str;
	char	*dst;

	i = -1;
	if (!split)
		return (-1);
	while (split[++i])
	{
		dst = ft_strjoin(split[i], "/");
		str = ft_strjoin(dst, (*command)[0]);
		if (access(str, F_OK) >= 0 && access(str, X_OK) >= 0)
		{
			ft_strdel(&((*command)[0]));
			(*command)[0] = str;
			ft_strdel(&dst);
			return (1);
		}
		ft_strdel(&str);
		ft_strdel(&dst);
	}
	return (-1);
}

static int	check_env_path(char ***command)
{
	int		result;
	char	*str;
	char	**split;

	str = value_line_path("PATH", 1);
	if (!str)
	{
		str = value_line_path("PATH", 0);
		if (!str)
			return (-1);
	}
	split = ft_strsplit(str, ':');
	result = path_of_commands(&(*command), split);
	ft_strdel(&str);
	ft_arraydel(&split);
	return (result);
}

int			is_in_path(char ***command)
{
	int		result;

	if ((!(*command)) || (!(*command)[0]))
		return (-1);
	result = check_env_path(command);
	if (result != -1)
		return (result);
	if (access((*command)[0], F_OK) >= 0 && access((*command)[0], X_OK) >= 0)
		return (1);
	return (result);
}
