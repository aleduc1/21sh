/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 14:54:24 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/28 11:18:42 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int			add_set_value(char *key, char *value)
{
	t_env	*my_env;
	int		verif;

	verif = 0;
	my_env = get_env(0, NULL);
	if (!value)
		value = "";
	if (str_is_alpha(key) == 0 || str_is_alpha(value) == 0)
		return (-2);
	while (my_env->next)
	{
		if (ft_strequ(my_env->key, key))
		{
			ft_strdel(&((my_env)->value));
			my_env->value = ft_strdup(value ? value : "");
			verif = 1;
			break ;
		}
		my_env = my_env->next;
	}
	if (verif == 0)
		verif = create_new_line_env(my_env, key, value, 0);
	return (verif);
}

int			ft_unset(char *key)
{
	int	verif;

	verif = free_maillon_env(key, 0);
	return (verif);
}

int			edit_set_command_env(char *str, t_env *my_env)
{
	int		verif;
	char	**spl;

	verif = 0;
	spl = ft_strsplit(str, '=');
	if (!spl)
		return (-1);
	while (my_env && my_env->next)
	{
		if (ft_strequ(my_env->key, spl[0]))
		{
			ft_strdel(&((my_env)->value));
			my_env->value = ft_strdup(spl[1] ? spl[1] : "");
			verif = 1;
			break ;
		}
		my_env = my_env->next;
	}
	if (verif == 0)
		verif = create_new_line_env(my_env, spl[0], spl[1], 0);
	if (verif != -1)
		verif = edit_export(spl[0]);
	ft_arraydel(&spl);
	return (verif);
}
