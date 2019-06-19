/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_hash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 14:52:42 by apruvost          #+#    #+#             */
/*   Updated: 2019/06/19 22:24:27 by apruvost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

extern t_hash		g_hash_deleted;
extern t_ht_hash	*g_hash_table;

static void			bt_hash_showall(void)
{
	ht_hash_show(g_hash_table);
}

static int			bt_addhash(char *av, int ret)
{
	char	*path;

	path = NULL;
	path = is_in_path(av);
	if (path != NULL)
	{
		ht_hash_insert(g_hash_table, av, path);
		ft_strdel(&path);
	}
	else
		ret = 1;
	return (ret);
}

int					bt_hash(char **av)
{
	int	i;
	int	ret;

	if (av[1] == NULL)
	{
		bt_hash_showall();
		return (0);
	}
	i = 1;
	ret = 0;
	while (av[i] != NULL)
	{
		if (!ft_strchr_exist(av[i], '/'))
			ret = bt_addhash(av[i], ret);
		++i;
	}
	return (ret);
}
