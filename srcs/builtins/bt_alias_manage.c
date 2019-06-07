/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_alias_manage.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 13:40:48 by apruvost          #+#    #+#             */
/*   Updated: 2019/06/07 16:27:28 by apruvost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_alias	*bt_alias_new(char **av, int i, t_alias *alias)
{
	char	*tmp;
	t_alias	*curr;

	tmp = ft_strchr('=', av[i]);
	*tmp = '\0';
	curr = (t_alias *)malloc(sizeof(t_alias));
	curr->key = ft_strdup(av[i]);
	curr->value = ft_strdup(&(tmp[1]));
	curr->next = &(*alias);
	tmp = '=';
	return (curr);
}

t_alias	*bt_alias_replace(char **av, int i, t_alias *alias)
{
	char	*tmp;
	t_alias *curr;

	tmp = ft_strchr('=', av[i]);
	*tmp = '\0';
	curr = alias;
	while (alias != NULL)
	{
		if (ft_strequ(av[i], alias->key))
		{
			ft_strdel(&curr->value);
			curr->value = ft_strdup(&(tmp[1]));
			*tmp = '=';
			return (curr);
		}
		alias = alias->next;
	}
	*tmp = '=';
	return (NULL);
}

t_alias	*bt_alias_get(char **av, int i, t_alias *alias)
{
	char	*tmp;
	t_alias *curr;

	tmp = ft_strchr('=', av[i]);
	*tmp = '\0';
	curr = alias;
	while (alias != NULL)
	{
		if (ft_strequ(av[i], alias->key))
		{
			*tmp = '=';
			return (curr);
		}
		alias = alias->next;
	}
	*tmp = '=';
	return (NULL);
}

int		bt_alias_exists(char **av, int i, t_alias *alias)
{
	char	*tmp;
	t_alias *curr;

	tmp = ft_strchr('=', av[i]);
	*tmp = '\0';
	curr = alias;
	while (alias != NULL)
	{
		if (ft_strequ(av[i], alias->key))
		{
			*tmp = '=';
			return (1);
		}
		alias = alias->next;
	}
	*tmp = '=';
	return (0);
}
