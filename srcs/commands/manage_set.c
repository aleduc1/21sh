/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 14:54:24 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/16 15:27:53 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int			edit_set(char *key, char *value)
{
	t_env	*my_env;
	t_env	*head;
	int		verif;

	my_env = get_env(0, NULL);
	head = my_env;
	verif = 0;
	if (!value)
		value = "";
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
	my_env = head;
	return (verif);
}

int			ft_unset(char *key)
{
	int	verif;

	verif = free_maillon_env(key, 0);
	return (verif);
}

int			edit_set_command_env(char *str)
{
	int		verif;
	char	**spl;

	spl = ft_strsplit(str, '=');
	if (!spl)
		return (-1);
	verif = edit_setenv(spl[0], spl[1]);
	if (spl)
		ft_arraydel(&spl);
	return (verif);
}
