/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 17:48:23 by sbelondr          #+#    #+#             */
/*   Updated: 2019/04/11 18:59:50 by sbelondr         ###   ########.fr       */
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

static void	init_variable(t_env **my_env)
{
	t_arg		*arg;

	arg = create_arg("?", "0");
	edit_set(arg, &(*my_env));
	free_arg(&arg);
	arg = create_arg("FD_OUTPUT", "1");
	edit_set(arg, &(*my_env));
	free_arg(&arg);
	arg = create_arg("FD_ERROR_OUTPUT", "2");
	edit_set(arg, &(*my_env));
	free_arg(&arg);
}

t_env		*init_env(void)
{
	t_env		*head;
	t_env		*current;
	extern char	**environ;
	int			i;
	char		**split;

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
	init_variable(&current);
	return (head);
}

int			free_maillon_env(t_env **my_env, char *key, int env)
{
	int		verif;
	t_env	*head;
	t_env	*last;

	head = (*my_env);
	last = NULL;
	verif = 0;
	while ((*my_env)->next)
	{
		if (ft_strequ((*my_env)->key, key) && (env == 0 ||
					(env == 1 && (*my_env)->see_env == 1)))
		{
			last->next = (*my_env)->next;
			ft_strdel(&((*my_env)->key));
			ft_strdel(&((*my_env)->value));
			free(*my_env);
			(*my_env) = NULL;
			verif = 1;
			break ;
		}
		last = (*my_env);
		(*my_env) = (*my_env)->next;
	}
	(*my_env) = head;
	return (verif);
}

void		free_env(t_env **lst)
{
	t_env	*tmp;

	while (*lst)
	{
		tmp = (*lst);
		(*lst) = (*lst)->next;
		ft_strdel(&(tmp->key));
		ft_strdel(&(tmp->value));
		free(tmp);
		tmp = NULL;
	}
}
