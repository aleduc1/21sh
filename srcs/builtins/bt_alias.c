/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_alias.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 17:00:16 by apruvost          #+#    #+#             */
/*   Updated: 2019/06/06 13:51:53 by apruvost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	bt_showalias(char **av, int i, t_alias *alias, int ret)
{
	t_alias	*curr;

	if (!bt_alias_exists(av, i, alias))
		return (1);
	curr = bt_alias_get(av, i, alias);
	ft_printf("%s=%s\n", curr->key, curr->value);
	return (ret);
}

t_alias		*bt_addalias(char **av, int i, t_alias *alias)
{
	int	len;

	len = av[i] - ft_strchr('=', av[i]);
	if (bt_alias_exists(av, i, alias))
		alias = bt_alias_replace(av, i, alias);
	else
		alias = bt_alias_new(av,i, alias);
	return (alias);
}

int			bt_alias(char **av)
{
	static t_alias	*alias = NULL;
	int				i;
	int				ret;

	i = 1;
	ret = 0;
	while (ac[i])
	{
		if (ft_strchr_exist('=', av[i]))
			alias = bt_addalias(av, i, &(*alias));
		else
			ret = bt_showalias(av, i, alias, ret);
		++i;
	}
	return (0);
}
