/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 17:36:44 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/08 13:55:39 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int		builtin_env_display(t_redirection *r)
{
	int		i;
	char	**lst_env;

	i = -1;
	lst_env = create_list_env(get_env(0), 1);
	while (lst_env[++i])
		ft_dprintf(r->out, "%s\n", lst_env[i]);
	if (i == 0)
		ft_dprintf(r->error, "You are nothing value in env\n");
	ft_arraydel(&lst_env);
	return (0);
}

char	*manip_command_env(char ***input, int index)
{
	char	*str;
	char	*tmp;
	char	*stock;

	if (!((*input)[index]))
		return (NULL);
	str = ft_strdup((*input)[index]);
	while ((*input)[++index])
	{
		stock = ft_strjoin(" ", (*input)[index]);
		tmp = ft_strjoin(str, stock);
		ft_strdel(&stock);
		ft_strdel(&str);
		str = ft_strdup(tmp);
		ft_strdel(&tmp);
	}
	return (str);
}

int		fuck_env(char **input, char **final)
{
	int		i;
	char	**str;

	i = 0;
	while (input[++i])
	{
		if (ft_strchr_exist(input[i], '='))
		{
			str = ft_strsplit(input[i], '=');
			edit_set_command_env(str[0], str[1]);
			ft_arraydel(&str);
		}
		else
		{
			if (ft_strchr_exist(input[i], '<') ||
						ft_strchr_exist(input[i], '>'))
				return (0);
			break ;
		}
	}
	(*final) = manip_command_env(&input, i);
	return (1);
}

int		check_is_env_command(char **input)
{
	char	*final;
	char	**str;
	int		verif;

	final = NULL;
	str = ft_strsplit(*input, 0);
	if (ft_strequ(str[0], "env") == 0 || (!str[1]))
	{
		ft_arraydel(&str);
		return (0);
	}
	verif = fuck_env(str, &final);
	if (final)
		ft_printf("%s|\n", final);
	if (verif == 1)
	{
		ft_strdel(&(*input));
		(*input) = final;
	}
	ft_arraydel(&str);
	return (1);
}

int		builtin_env(t_redirection *r, char **argv)
{
	int		verif;

	verif = 0;
	verif = builtin_env_display(r);
	return (verif);
}

int		builtin_set(t_redirection *r)
{
	int		i;
	char	**lst_env;

	lst_env = create_list_env(get_env(0), 0);
	i = -1;
	while (lst_env[++i])
		ft_dprintf(r->out, "%s\n", lst_env[i]);
	if (i == 0)
		ft_dprintf(r->error, "You are nothing value in env\n");
	ft_arraydel(&lst_env);
	return (0);
}
