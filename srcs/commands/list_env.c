/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 17:48:23 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/17 14:19:05 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

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