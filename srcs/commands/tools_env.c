/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 17:29:22 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/16 15:10:03 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/env.h"

int			create_new_line_env(t_env *my_env, char *key, char *value, int env)
{
	while (my_env->next)
		my_env = my_env->next;
	my_env->key = ft_strdup(key);
	my_env->value = ft_strdup(value);
	my_env->see_env = env;
	my_env->next = init_maillon_env();
	return (0);
}

char		*value_line_path(char *key, int env)
{
	t_env	*my_env;
	char	*dst;

	my_env = get_env(0);
	dst = NULL;
	while (my_env)
	{
		if (ft_strequ(my_env->key, key))
		{
			if (env == 0 || (env == my_env->see_env))
			{
				dst = ft_strdup(my_env->value);
				return (dst);
			}
			else
				return (NULL);
		}
		my_env = my_env->next;
	}
	return (dst);
}
