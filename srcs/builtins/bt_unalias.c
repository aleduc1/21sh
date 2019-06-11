/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_unalias.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 17:00:29 by apruvost          #+#    #+#             */
/*   Updated: 2019/06/11 17:10:24 by apruvost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

extern t_ht_alias	*g_alias_table;

int		bt_unalias(char **av)
{
	int		i;
	int		ret;

	i = 1;
	ret = 0;
	if (!av[1])
	{
		ft_dprintf(2, "unalias: not enough arguments\n");
		return (1);
	}
	while (av[i])
	{
		if (ht_alias_search(g_alias_table, av[i]) != NULL)
			ht_alias_delete(g_alias_table, av[i]);
		else
		{
			ft_dprintf(2, "unalias: no such hash table element: %s\n", av[i]);
			ret = 1;
		}
		++i;
	}
	return (ret);
}
