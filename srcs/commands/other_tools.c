/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 17:57:48 by sbelondr          #+#    #+#             */
/*   Updated: 2019/06/06 18:36:38 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "builtins.h"
#include "job.h"

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

/*
** search if it's a builtin
**	return 0 if it's a builtin and if it's command work
**	return -2 if it's a builtin and if it's command not work
**	return -1 if it's not a builtin
*/

int			is_builtin_env(t_job *j, char **av)
{
	int	verif;

	if (ft_strequ(av[0], "env"))
		verif = builtin_env(j->r, av);
	else if (ft_strequ(av[0], "set"))
		verif = builtin_set(j->r);
	else if (ft_strequ(av[0], "setenv"))
		verif = edit_setenv(av[1], av[2]);
	else if (ft_strequ(av[0], "unsetenv"))
		verif = ft_unsetenv(av[1]);
	else if (ft_strequ(av[0], "export"))
		verif = bt_export(av + 1);
	else if (ft_strequ(av[0], "unset"))
		verif = ft_unset(av[1]);
	else if (ft_strchr_exist(av[0], '='))
		verif = edit_set(av, j->r);
	else
		verif = -1;
	return (verif);
}

int			is_builtin(t_job *j, t_pos *pos)
{
	int		verif;
	char	**av;

	av = j->first_process->cmd;
	verif = is_builtin_env(j, av);
	if (verif != -1)
		return (verif);
	if (ft_strequ(av[0], "echo"))
		verif = bt_echo(av, j->r);
	else if (ft_strequ(av[0], "cd"))
		verif = (builtin_cd(av) < 0) ? -2 : 0;
	else if (ft_strequ(av[0], "exit"))
		verif = bt_exit(j);
	else if (ft_strequ(av[0], "jobs"))
		verif = bt_jobs(av);
	else if (ft_strequ(av[0], "fg"))
		verif = bt_fg();
	else if (ft_strequ(av[0], "bg"))
		verif = bt_bg();
	else if (ft_strequ(av[0], "fc"))
		verif = builtin_fc(av, pos); // -2 si erreur ou 0 si ok
	else
		verif = -1;
	return (verif);
}

/*
** edit the local variable ('?') for know if the last command
** has worked
*/

int			gest_return(int verif)
{
	char	*value;

	verif = (verif == 256 || verif < 0) ? -1 : 0;
	value = ft_itoa(verif);
	verif = add_set_value("?", value);
	ft_strdel(&value);
	return (verif);
}

/*
** is_end = 1 -> free env
** f_line is not null -> modify head env by f_line
*/

t_env		*get_env(int is_end, t_env *head)
{
	static t_env	*my_env;

	if (is_end == 3 && (!my_env))
		return (NULL);
	if ((!my_env) && (!head))
	{
		my_env = init_env();
		init_variable();
	}
	if (head)
		my_env = head;
	if (is_end == 1)
		free_env(&my_env);
	return (my_env);
}
