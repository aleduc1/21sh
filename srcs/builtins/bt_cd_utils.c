/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 17:22:06 by apruvost          #+#    #+#             */
/*   Updated: 2019/05/07 16:28:50 by apruvost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int		getnextpath(char *path)
{
	int	i;

	i = 0;
	while (path[i] != '\0' && path[i] != ':')
		i++;
	if (path[i] != '\0')
		return (i + 1);
	return (i);
}

int		cd_testpath(char *path, char *directory, char **test)
{
	int		i;
	char	*tmp;

	i = ft_strlen(path);
	if (path[i - 1] == '/')
		tmp = ft_strjoin(path, directory);
	else
		tmp = ft_jointhree(path, "/", directory);
	if (access(tmp, F_OK) == 0)
	{
		*test = tmp;
		return (1);
	}
	ft_strdel(&tmp);
	return (0);
}

/*
** Function to test a pathname of CDPATH
*/

int		cd_testcdpath(char *path, char *directory, char **test)
{
	int		i;
	int		j;
	char	*tmp;

	i = ft_getnextpath(path);
	if ((tmp = (char *)malloc(sizeof(char) * (i + 1))) == NULL)
	{
		dprintf(2, "21sh: cd: Failed to malloc\n");			// NO MEMORY
		return (0);
	}
	j = cd_testpath(tmp, directory, test);
	ft_strdel(&tmp);
	return (j);
}

/*
** Function to get arguments
*/

int		cd_getargs(char **av, t_cd *cd)
{
	int	i;
	int	j;

	i = 1;

	while (av[i])
	{
		if (av[i][0] == '-')
		{
			j = 1;
			while (av[i][j] != '\0' && (av[i][j] == 'L' || av[i][j] == 'P'))
				j++;
			if (av[i][j] == '\0')
			{
				if (av[i][j - 1] == 'L')
				{
					cd->arg_L = 1;
					cd->arg_P = 1;
				}
				else if (av[i][j - 1] == 'P')
				{
					cd->arg_L = 1;
					cd->arg_P = 1;
				}
				else
					return (i);
				i++;
			}
			else 
				return (i);
		}
		else
			return (i);
	}
	return (i);
}
