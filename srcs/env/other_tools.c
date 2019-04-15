/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 17:57:48 by sbelondr          #+#    #+#             */
/*   Updated: 2019/04/15 11:34:00 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "env.h"
#include "../../includes/env.h"

/*
** creer la commande depuis la struct t_arg pour pouvoir execve
*/

char	**transfer_arg(t_arg *lst_arg)
{
	int		i;
	t_arg	*head;
	char	**split;

	i = 0;
	head = lst_arg;
	while (lst_arg)
	{
		i++;
		lst_arg = lst_arg->next;
	}
	if (!(split = (char**)malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	i = -1;
	lst_arg = head;
	while (lst_arg->value)
	{
		split[++i] = ft_strdup(lst_arg->value);
		lst_arg = lst_arg->next;
	}
	split[++i] = NULL;
	lst_arg = head;
	return (split);
}

int		is_in_path(char ***command, t_env *my_env)
{
	int		i;
	char	*str;
	char	*dst;
	char	**split;

	if ((!(*command)) || (!(*command)[0]))
		return (-1);
	if (access((*command)[0], F_OK) >= 0 && access((*command)[0], X_OK) >= 0)
		return (1);
	str = value_line_path(my_env, "PATH", 0);
	if (!str)
		return (-1);
	split = ft_strsplit(str, ':');
	i = -1;
	while (split[++i])
	{
		dst = ft_strjoin(split[i], "/");
		ft_strdel(&str);
		str = ft_strjoin(dst, (*command)[0]);
		if (access(str, F_OK) >= 0 && access(str, X_OK) >= 0)
		{
			ft_strdel(&((*command)[0]));
			(*command)[0] = ft_strdup(str);
			ft_strdel(&str);
			ft_strdel(&dst);
			ft_arraydel(&split);
			return (1);
		}
		ft_strdel(&dst);
	}
	ft_strdel(&str);
	ft_arraydel(&split);
	return (-1);
}

int		is_builtin(char **command, t_env **my_env, int fd_stock[3])
{
	t_arg	*arg;
	int		verif;

	if (command[1] && command[2])
		arg = create_arg(command[1], command[2]);
	else
		arg = NULL;
	if (ft_strequ(command[0], "env"))
		verif = builtin_env(&(*my_env), fd_stock);
	else if (ft_strequ(command[0], "set"))
		verif = builtin_set(&(*my_env), fd_stock);
	else if (ft_strequ(command[0], "setenv"))
		verif = edit_setenv(arg, &(*my_env));
	else if (ft_strequ(command[0], "unsetenv"))
		verif = ft_unsetenv(command[1], &(*my_env));
	else if (ft_strequ(command[0], "export"))
		verif = edit_export(command[1], &(*my_env));
	else if (ft_strequ(command[0], "unset"))
		verif = ft_unset(command[1], &(*my_env));
	else if (ft_strequ(command[0], "editset"))
		verif = edit_set(arg, &(*my_env));
	else if (ft_strequ(command[0], "exit"))
		verif = 2;
	else
		verif = -1;
	free_arg(&arg);
	return (verif);
}

int		gest_return(int verif, t_env **my_env)
{
	t_arg	*arg;
	char	*value;

	value = ft_itoa(verif);
	arg = create_arg("?", value);
	ft_strdel(&value);
	verif = edit_set(arg, &(*my_env));
	free_arg(&arg);
	return (verif);
}
