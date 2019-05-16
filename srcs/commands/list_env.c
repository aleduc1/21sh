/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 17:48:23 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/16 15:27:44 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/env.h"

t_env		*init_maillon_env(void)
{
	t_env	*lst;

	if (!(lst = (t_env*)malloc(sizeof(t_env) * 1)))
		return (NULL);
	lst->key = NULL;
	lst->value = NULL;
	lst->see_env = 0;
	lst->next = NULL;
	return (lst);
}

void		init_variable(void)
{
	edit_set("?", "0");
	edit_set("FD_OUTPUT", "1");
	edit_set("FD_ERROR_OUTPUT", "2");
}

t_env		*init_env(void)
{
	int			i;
	char		**split;
	t_env		*head;
	t_env		*current;
	extern char	**environ;

	i = -1;
	current = init_maillon_env();
	head = current;
	if (!environ)
		return (NULL);
	while (environ[++i])
	{
		split = ft_strsplit(environ[i], '=');
		current->key = ft_strdup(split[0]);
		current->value = ft_strdup(split[1] ? split[1] : "");
		current->see_env = 1;
		ft_arraydel(&split);
		current->next = init_maillon_env();
		current = current->next;
	}
	return (head);
}

static int	free_that(t_env *my_env, t_env *last)
{
	int	verif;

	verif = 0;
	if (last)
		last->next = my_env->next;
	else
	{
		last = my_env->next;
		verif = 1;
	}
	ft_strdel(&(my_env->key));
	ft_strdel(&(my_env->value));
	free(my_env);
	my_env = NULL;
	if (verif)
		get_env(0, last);
	return (1);
}

int			free_maillon_env(char *key, int env)
{
	int		verif;
	t_env	*my_env;
	t_env	*last;
	int		test;

	my_env = get_env(0, NULL);
	last = NULL;
	verif = 0;
	test = 0;
	while (my_env->next)
	{
		if (ft_strequ(my_env->key, key) && (env == 0 ||
					(env == 1 && my_env->see_env == 1)))
		{
			verif = free_that(my_env, last);
			break ;
		}
		last = my_env;
		my_env = my_env->next;
	}
	return (verif);
}

void		free_env(t_env **lst)
{
	if ((*lst)->next)
		free_env(&((*lst)->next));
	ft_strdel(&((*lst)->key));
	ft_strdel(&((*lst)->value));
	free(*lst);
	(*lst) = NULL;
}
