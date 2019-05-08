/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 21:20:48 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/08 16:41:29 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static int	cnt_arg(char ***arguments)
{
	int	i;

	i = 0;
	while ((*arguments)[i])
		i++;
	if (i == 2)
	{
		i = check_arg(&(*arguments));
		return (i);
	}
	else if (i == 1)
		return (1);
	else
	{
		ft_dprintf(2, "Too many args for cd command\n");
		return (-1);
	}
}

static int	simple_cd(char ***arguments, char *mot_clef)
{
	char	*line;

	line = value_line_path(mot_clef, 0);
	if (!line)
		return (-1);
	ft_strdel(&((*arguments)[1]));
	ft_strdel(&((*arguments)[2]));
	(*arguments)[1] = line;
	(*arguments)[2] = 0;
	return (1);
}

static int	search_rules_cd(char ***arguments)
{
	int	verif;

	verif = 0;
	verif = cnt_arg(&(*arguments));
	if (verif == 1)
		verif = simple_cd(&(*arguments), "HOME");
	else if (verif == 2)
		verif = simple_cd(&(*arguments), "OLDPWD");
	return (verif);
}

static int	check_return(char **arguments, int verif)
{
	char	*list;
	char	*stock;

	if (ft_strequ(arguments[1], ".."))
	{
		list = value_line_path("PWD", 0);
		if (list)
		{
			stock = ft_strsub(list, 0, ft_lastchr(list, '/'));
			ft_strdel(&list);
			if (stock)
			{
				verif = chdir(stock);
				ft_strdel(&stock);
				return (verif);
			}
		}
	}
	return (verif);
}

int			builtin_cd(char **arguments)
{
	int			verif;
	char		buf[BUF_S];

	if (ft_arraylen(arguments) > 2)
		error_cd(1, NULL);
	if (ft_arraylen(arguments) > 2)
		return (-2);
	verif = search_rules_cd(&arguments);
	ft_bzero(buf, BUF_S);
	getcwd(buf, BUF_S);
	(verif >= 0) ? verif = chdir(arguments[1]) : 0;
	(verif < 0) ? verif = check_return(arguments, verif) : 0;
	if (verif >= 0)
	{
		edit_set("OLDPWD", buf);
		ft_bzero(buf, BUF_S);
		getcwd(buf, BUF_S);
		edit_set("PWD", buf);
	}
	else
		error_cd(verif, arguments[1]);
	return (verif);
}
