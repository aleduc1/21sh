/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 17:57:48 by sbelondr          #+#    #+#             */
/*   Updated: 2019/06/15 19:02:52 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/*
** search if it's a builtin
** return 0 if it's a builtin and if it's command work
** return -2 if it's a builtin and if it's command not work
** return -1 if it's not a builtin
*/

int			verif_set(char **argv, int nb, t_redirection *r, char *name)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	if (nb == i || (nb == 3 && i == 2))
		return (1);
	else if (i > nb)
		ft_dprintf(r->error, "21sh: %s: Too many arguments.\n", name);
	else
	{
		if (ft_strequ(name, "setenv"))
			builtin_env_display(r);
		else
			ft_dprintf(r->error, "21sh: %s: Too few arguments.\n", name);
	}
	return (0);
}

int			is_builtin_bis(char **argv, t_redirection *r)
{
	int	verif;

	verif = 0;
	if (ft_strequ(argv[0], "env"))
		verif = builtin_env(r, argv);
	else if (ft_strequ(argv[0], "set"))
		verif = builtin_set(r);
	else if (ft_strequ(argv[0], "setenv"))
		verif = verif_set(argv, 3, r, "setenv")
			? edit_setenv(argv[1], argv[2]) : -2;
	else if (ft_strequ(argv[0], "unsetenv"))
		verif = verif_set(argv, 2, r, "unsetenv")
			? ft_unsetenv(argv[1]) : 0;
	else
		verif = -1;
	return (verif);
}

int			is_builtin(char **argv, t_redirection *r)
{
	int		verif;

	if ((verif = is_builtin_bis(argv, r)) != -1)
		;
	else if (ft_strequ(argv[0], "export"))
		verif = verif_set(argv, 2, r, "export") ? edit_export(argv[1]) : 0;
	else if (ft_strequ(argv[0], "unset"))
		verif = verif_set(argv, 2, r, "unset") ? ft_unset(argv[1]) : 0;
	else if (ft_strequ(argv[0], "editset"))
		verif = verif_set(argv, 3, r, "editset")
			? add_set_value(argv[1], argv[2]) : -2;
	else if (ft_strequ(argv[0], "echo"))
		verif = bt_echo(argv, r);
	else if (ft_strequ(argv[0], "cd"))
		verif = (builtin_cd(argv, r)) ? -2 : 0;
	else if (ft_strequ(argv[0], "exit"))
		verif = bt_exit(argv);
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
