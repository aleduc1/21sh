/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 14:54:24 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/06 04:57:00 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/env.h"

static int	count_env(t_env *my_env, int env)
{
	int	len;

	len = 0;
	while (my_env->next)
	{
		if (env == 0 || (env == 1 && my_env->see_env == 1))
			len++;
		my_env = my_env->next;
	}
	return (len);
}

char		**create_list_env(t_env *my_env, int env)
{
	char	*str;
	t_env	*head;
	char	**dst;
	int		len;

	head = my_env;
	len = count_env(my_env, env);
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

int			edit_export(char *key, t_env **my_env)
{
	int		verif;
	t_env	*head;

	head = (*my_env);
	verif = 0;
	while ((*my_env)->next)
	{
		if (ft_strequ((*my_env)->key, key))
		{
			verif = 1;
			(*my_env)->see_env = 1;
			break ;
		}
		(*my_env) = (*my_env)->next;
	}
	(*my_env) = head;
	return (verif);
}

int			edit_set(t_arg *arg, t_env **my_env)
{
	t_env	*head;
	int		verif;

	head = (*my_env);
	verif = 0;
	while ((*my_env)->next)
	{
		if (ft_strequ((*my_env)->key, arg->key))
		{
			ft_strdel(&((*my_env)->value));
			(*my_env)->value = ft_strdup(arg->value ? arg->value : "");
			verif = 1;
			break ;
		}
		(*my_env) = (*my_env)->next;
	}
	if (verif == 0)
		verif = create_new_path(*my_env, arg, 0);
	(*my_env) = head;
	return (verif);
}
/*
int			edit_set_cmd(t_cmd *cmd, t_env **my_env)
{
	int		verif;
	t_arg	*arg;

	arg = create_arg(cmd->argv[1], cmd->argv[2]);
	verif = edit_set(arg, &(*my_env));
	free_arg(&arg);
	return (verif);
}
*//*
int			edit_setenv(t_cmd *cmd, t_env **my_env)
{
	int	verif;
	t_arg	*arg;

	arg = create_arg(cmd->argv[1], cmd->argv[2]);
	verif = edit_set(arg, &(*my_env));
	if (arg->key)
		edit_export(arg->key, &(*my_env));
	free_arg(&arg);
	return (verif);
}
*/
int			ft_unsetenv(char *key, t_env **my_env)
{
	int		verif;
	t_env	*head;

	head = (*my_env);
	verif = 0;
	while ((*my_env)->next)
	{
		if (ft_strequ((*my_env)->key, key))
		{
			(*my_env)->see_env = 0;
			verif = 1;
			break ;
		}
		(*my_env) = (*my_env)->next;
	}
	(*my_env) = head;
	return (verif);
}

int			ft_unset(char *key, t_env **my_env)
{
	int	verif;

	verif = free_maillon_env(&(*my_env), key, 0);
	return (verif);
}
