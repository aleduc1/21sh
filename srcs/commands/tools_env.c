/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 17:29:22 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/08 14:49:25 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/env.h"

int			is_env_empty(char *key)
{
	char *test;

	test = value_line_path(key, 0);
	if (test == NULL)
		return (1);
	else if (ft_strequ(test, ""))
	{
		ft_strdel(&test);
		return (1);
	}
	ft_strdel(&test);
	return (0);
}

int			create_new_path_env(char *key, char *value, int env)
{
	t_env	*head;

	head = init_maillon_env();
	head->key = ft_strdup(key);
	head->value = ft_strdup(value ? value : "");
	head->see_env = env;
	head->next = NULL;
	get_env(0, head);
	return (0);
}

int			create_new_path(t_env *my_env, char *key, char *value, int env)
{
	while (my_env->next)
		my_env = my_env->next;
	my_env->key = ft_strdup(key);
	my_env->value = ft_strdup(value);
	my_env->see_env = env;
	my_env->next = init_maillon_env();
	return (0);
}

int			search_line_env(t_env *my_env, char *key, int env)
{
	if (!(my_env && key))
		return (-1);
	while (my_env->next)
	{
		if (ft_strequ(my_env->key, key))
		{
			if (my_env->see_env == env || env == 0)
				return (1);
			else
				return (0);
		}
		my_env = my_env->next;
	}
	return (0);
}

char		*value_line_path(char *key, int env)
{
	t_env	*my_env;
	char	*dst;

	my_env = get_env(0, NULL);
	dst = NULL;
	while (my_env)
	{
		if (ft_strequ(my_env->key, key))
		{
			if (env == 0 || (env == my_env->see_env) || my_env->see_env == 3)
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
