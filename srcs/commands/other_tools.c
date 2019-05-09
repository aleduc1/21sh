/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 17:57:48 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/09 03:40:18 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "builtins.h"

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
	str = value_line_path("PATH", 0);
	if (!str)
		return (-1);
	split = ft_strsplit(str, ':');
	result = path_of_commands(&(*command), split);
	ft_strdel(&str);
	ft_arraydel(&split);
	return (result);
}

int			is_builtin(char **argv, t_redirection *r)
{
	int		verif;

	if (ft_strequ(argv[0], "env"))
		verif = builtin_env(r, argv);
	else if (ft_strequ(argv[0], "set"))
		verif = builtin_set(r);
	else if (ft_strequ(argv[0], "setenv"))
		verif = edit_setenv(argv[1], argv[2]);
	else if (ft_strequ(argv[0], "unsetenv"))
		verif = ft_unsetenv(argv[1]);
	else if (ft_strequ(argv[0], "export"))
		verif = edit_export(argv[1]);
	else if (ft_strequ(argv[0], "unset"))
		verif = ft_unset(argv[1]);
	else if (ft_strequ(argv[0], "editset"))
		verif = edit_set(argv[1], argv[2]);
	else if (ft_strequ(argv[0], "echo"))
		verif = bt_echo(argv, r);
	else if (ft_strequ(argv[0], "cd"))
		verif = (builtin_cd(argv) < 0) ? -2 : 0;
	else if (ft_strequ(argv[0], "exit"))
		verif = bt_exit(argv);
	else
		verif = -1;
	return (verif);
}

int			gest_return(int verif)
{
	char	*value;

	verif = (verif == 256 || verif < 0) ? -1 : 0;
	value = ft_itoa(verif);
	verif = edit_set("?", value);
	ft_strdel(&value);
	return (verif);
}

t_env		*get_env(int is_end, t_env *f_line)
{
	static t_env	*my_env;

	if (my_env == NULL)
	{
		my_env = init_env();
		init_variable();
	}
	if (f_line)
	{
		if (f_line->next == NULL)
			f_line->next = my_env;
		my_env = f_line;
	}
	if (is_end)
		free_env(&my_env);
	return (my_env);
}
