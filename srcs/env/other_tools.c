/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 17:57:48 by sbelondr          #+#    #+#             */
/*   Updated: 2019/04/11 14:31:54 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

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

	if (access((*command)[0], F_OK) >= 0 && access((*command)[0], X_OK) >= 0)
		return (1);
	str = value_line_path(my_env, "PATH", 1);
	if (!str)
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

int		is_builtin(t_arg *arg, t_env **my_env)
{
	t_arg	*final;
	char	*command;

	final = init_arg();
	command = ft_strdup(arg->value);
	final->key = ft_strdup(arg->value);
	final->value = ft_strdup(arg->next ? arg->next->value : "");
	if (ft_strequ(command, "env"))
		builtin_env(&(*my_env));
	else if (ft_strequ(command, "set"))
		builtin_set(&(*my_env));
	else if (ft_strequ(command, "setenv"))
		edit_setenv(&(*my_env), final);
	else if (ft_strequ(command, "unsetenv"))
		ft_unsetenv(&(*my_env), final->key);
	else if (ft_strequ(command, "export"))
		edit_export(&(*my_env), final->key);
	else if (ft_strequ(command, "unset"))
		ft_unset(&(*my_env), final->key);
	else if (ft_strequ(command, "editset"))
		edit_set(&(*my_env), final);
	else if (ft_strequ(command, "exit"))
	{
		ft_strdel(&command);
		free_arg(&final);
		return (2);
	}
	else
	{
		ft_strdel(&command);
		free_arg(&final);
		return (0);
	}
	ft_strdel(&command);
	free_arg(&final);
	return (1);
}

int		gest_return(int verif, t_env **my_env)
{
	t_arg	*arg;
	char	*value;

	value = ft_itoa(verif);
	arg = create_arg("?", value);
	ft_strdel(&value);
	verif = edit_set(&(*my_env), arg);
	free_arg(&arg);
	return (verif);
}
