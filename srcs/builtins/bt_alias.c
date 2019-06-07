/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_alias.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 17:00:16 by apruvost          #+#    #+#             */
/*   Updated: 2019/06/07 15:38:22 by apruvost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

extern t_alias	*g_alias;

static int		bt_showalias(char **av, int i, t_alias *alias, int ret)
{
	t_alias	*curr;

	if (!bt_alias_exists(av, i, alias))
		return (1);
	curr = bt_alias_get(av, i, alias);
	ft_printf("%s=%s\n", curr->key, curr->value);
	return (ret);
}

t_alias			*bt_addalias(char **av, int i, t_alias *alias)
{
	int	len;

	len = av[i] - ft_strchr('=', av[i]);
	if (bt_alias_exists(av, i, alias))
		alias = bt_alias_replace(av, i, &(*alias));
	else
		alias = bt_alias_new(av, i, &(*alias));
	return (alias);
}

int				bt_alias(char **av)
{
	t_alias	*alias;
	int		i;
	int		ret;

	i = 1;
	ret = 0;
	alias = g_alias;
	while (av[i])
	{
		if (ft_strchr_exist('=', av[i]))
			alias = bt_addalias(av, i, &(*alias));
		else
			ret = bt_showalias(av, i, alias, ret);
		++i;
	}
	ft_set_alias(&(*alias));
	return (ret);
}
