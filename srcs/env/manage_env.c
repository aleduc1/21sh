/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 14:54:24 by sbelondr          #+#    #+#             */
/*   Updated: 2019/06/02 18:18:37 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static int	count_env(int env)
{
	t_env	*my_env;
	t_env	*head;
	int		len;

	len = 0;
	my_env = get_env(0, NULL);
	head = my_env;
	while (my_env->next)
	{
		if (env == 0 || (env == 1 && my_env->see_env == 1))
			len++;
		my_env = my_env->next;
	}
	my_env = head;
	return (len);
}

char		**create_list_env(t_env *my_env, int env)
{
	char	*str;
	t_env	*head;
	char	**dst;
	int		len;

	head = my_env;
	len = count_env(env);
	my_env = head;
	if (!(dst = (char**)malloc(sizeof(char*) * (len + 1))))
		return (NULL);
	len = -1;
	while (my_env->next)
	{
		if (env == 0 || (env == 1 && my_env->see_env == 1))
		{
			str = ft_strjoin(my_env->key, "=");
			dst[++len] = ft_strjoin(str, my_env->value ? my_env->value : "");
			ft_strdel(&str);
		}
		my_env = my_env->next;
	}
	dst[++len] = NULL;
	my_env = head;
	return (dst);
}

int			edit_export(char *key)
{
	int		verif;
	t_env	*head;
	t_env	*my_env;

	my_env = get_env(0, NULL);
	head = my_env;
	verif = 0;
	while (my_env->next)
	{
		if (ft_strequ(my_env->key, key))
		{
			verif = 1;
			my_env->see_env = 1;
			break ;
		}
		my_env = my_env->next;
	}
	my_env = head;
	return (verif);
}

int			edit_setenv(char *key, char *value)
{
	int	verif;

	if (!key)
		return (-2);
	if (!value)
		value = "";
	verif = add_set_value(key, value);
	if (verif != -1)
		verif = edit_export(key);
	return (verif);
}

int			ft_unsetenv(char *key)
{
	int		verif;
	t_env	*head;
	t_env	*my_env;

	my_env = get_env(0, NULL);
	head = my_env;
	verif = 0;
	while (my_env->next)
	{
		if (ft_strequ(my_env->key, key))
		{
			my_env->see_env = 0;
			verif = 1;
			break ;
		}
		my_env = my_env->next;
	}
	my_env = head;
	return (verif);
}
