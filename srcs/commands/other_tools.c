/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 17:57:48 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/06 05:15:15 by sbelondr         ###   ########.fr       */
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

int			is_in_path(char ***command)
{
	int		result;
	char	*str;
	char	**split;

	if ((!(*command)) || (!(*command)[0]))
		return (-1);
	if (access((*command)[0], F_OK) >= 0 && access((*command)[0], X_OK) >= 0)
		return (1);
	str = value_line_path(get_env(), "PATH", 0);
	if (!str)
		return (-1);
	split = ft_strsplit(str, ':');
	result = path_of_commands(&(*command), split);
	ft_strdel(&str);
	ft_arraydel(&split);
	return (result);
}

int			is_builtin(char **argv, t_lex *lex)
{
	int		verif;

	if (ft_strequ(argv[0], "env"))
		verif = 1;//verif = builtin_env(&(*my_env), cmd);
	else if (ft_strequ(argv[0], "set"))
		verif = 1;//verif = builtin_set(&(*my_env), cmd);
	else if (ft_strequ(argv[0], "setenv"))
		verif = 1;//verif = edit_setenv(cmd, &(*my_env));
	else if (ft_strequ(argv[0], "unsetenv"))
		verif = 1;//verif = ft_unsetenv(argv[1], &(*my_env));
	else if (ft_strequ(argv[0], "export"))
		verif = 1;//verif = edit_export(argv[1], &(*my_env));
	else if (ft_strequ(argv[0], "unset"))
		verif = 1;//verif = ft_unset(argv[1], &(*my_env));
	else if (ft_strequ(argv[0], "editset"))
		verif = 1;//verif = edit_set_cmd(cmd, &(*my_env));
	else if (ft_strequ(argv[0], "echo"))
		verif = -1;
	else if (ft_strequ(argv[0], "cd"))
		verif = 1;
	else if (ft_strequ(argv[0], "exit"))
		verif = 2;
	else
		verif = -1;
	return (verif);
}

int			gest_return(int verif)
{
	t_arg	*arg;
	char	*value;

	value = ft_itoa(verif);
	arg = create_arg("?", value);
	ft_strdel(&value);
	//verif = edit_set(arg);
	free_arg(&arg);
	return (verif);
}

t_env		*get_env(void)
{
	static t_env	*my_env;

	if (my_env == NULL)
		my_env = init_env();
	return (my_env);
}
