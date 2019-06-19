/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 17:57:48 by sbelondr          #+#    #+#             */
/*   Updated: 2019/06/19 21:50:42 by apruvost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/*
** search if it's a builtin
** return 0 if it's a builtin and if it's command work
** return -2 if it's a builtin and if it's command not work
** return -1 if it's not a builtin
*/

int			is_builtin(char **argv, t_redirection *r)
{
	int		verif;

	if (ft_strequ(argv[0], "env"))
		verif = builtin_env(r, argv);
	else if (ft_strequ(argv[0], "set"))
		verif = builtin_set(r);
	else if (ft_strequ(argv[0], "setenv"))
		verif = argv[1] ? edit_setenv(argv[1], argv[2]) : -2;
	else if (ft_strequ(argv[0], "unsetenv"))
		verif = ft_unsetenv(argv[1]);
	else if (ft_strequ(argv[0], "export"))
		verif = edit_export(argv[1]);
	else if (ft_strequ(argv[0], "unset"))
		verif = ft_unset(argv[1]);
	else if (ft_strequ(argv[0], "editset"))
		verif = argv[1] ? add_set_value(argv[1], argv[2]) : -2;
	else if (ft_strequ(argv[0], "echo"))
		verif = bt_echo(argv, r);
	else if (ft_strequ(argv[0], "cd"))
		verif = (bt_cd(argv)) ? -2 : 0;
	else if (ft_strequ(argv[0], "exit"))
		verif = bt_exit(argv);
	else if (ft_strequ(argv[0], "alias"))
		verif = bt_alias(argv);
	else if (ft_strequ(argv[0], "unalias"))
		verif = bt_unalias(argv);
	else if (ft_strequ(argv[0], "hash"))
		verif = bt_hash(argv);
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

	if (verif > 255)
		verif %= 255;
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
