/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 17:57:48 by sbelondr          #+#    #+#             */
/*   Updated: 2019/04/30 09:42:21 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/env.h"

/*
** creer la commande depuis la struct t_arg pour pouvoir execve
*/

char		**transfer_arg(t_arg *lst_arg)
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

static int	path_of_commands(char ***command, char **split)
{
	int		i;
	char	*str;
	char	*dst;

	i = -1;
	while (split[++i])
	{
		dst = ft_strjoin(split[i], "/");
		str = ft_strjoin(dst, (*command)[0]);
		if (access(str, F_OK) >= 0 && access(str, X_OK) >= 0)
		{
			ft_strdel(&((*command)[0]));
			(*command)[0] = ft_strdup(str);
			ft_strdel(&str);
			ft_strdel(&dst);
			return (1);
		}
		ft_strdel(&str);
		ft_strdel(&dst);
	}
	return (-1);
}

int			is_in_path(char ***command, t_env *my_env)
{
	int		result;
	char	*str;
	char	**split;

	if ((!(*command)) || (!(*command)[0]))
		return (-1);
	if (access((*command)[0], F_OK) >= 0 && access((*command)[0], X_OK) >= 0)
		return (1);
	str = value_line_path(my_env, "PATH", 0);
	if (!str)
		return (-1);
	split = ft_strsplit(str, ':');
	result = path_of_commands(&(*command), split);
	ft_strdel(&str);
	ft_arraydel(&split);
	return (result);
}

int			is_builtin(t_cmd *cmd, t_env **my_env)
{
	int		verif;

	if (ft_strequ(cmd->argv[0], "env"))
		verif = builtin_env(&(*my_env), cmd);
	else if (ft_strequ(cmd->argv[0], "set"))
		verif = builtin_set(&(*my_env), cmd);
	else if (ft_strequ(cmd->argv[0], "setenv"))
		verif = edit_setenv(cmd, &(*my_env));
	else if (ft_strequ(cmd->argv[0], "unsetenv"))
		verif = ft_unsetenv(cmd->argv[1], &(*my_env));
	else if (ft_strequ(cmd->argv[0], "export"))
		verif = edit_export(cmd->argv[1], &(*my_env));
	else if (ft_strequ(cmd->argv[0], "unset"))
		verif = ft_unset(cmd->argv[1], &(*my_env));
	else if (ft_strequ(cmd->argv[0], "editset"))
		verif = edit_set_cmd(cmd, &(*my_env));
	else if (ft_strequ(cmd->argv[0], "echo"))
		verif = -1;
	else if (ft_strequ(cmd->argv[0], "cd"))
		verif = 1;
	else if (ft_strequ(cmd->argv[0], "exit"))
		verif = 2;
	else
		verif = -1;
	return (verif);
}

int			gest_return(int verif, t_env **my_env)
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
