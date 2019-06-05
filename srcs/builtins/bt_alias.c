/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_alias.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 17:00:16 by apruvost          #+#    #+#             */
/*   Updated: 2019/06/05 02:08:22 by apruvost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_alias	*bt_addalias(char **av, int i, t_alias *alias)
{
	int	len;

	len = ft_strchr('=', av[i]) - av[i];
}

int		bt_alias(char **av)
{
	static t_alias	*alias = NULL;
	int				i;

	i = 1;
	while (ac[i])
	{
		if (ft_strchr_exist('=', av[i]))
			alias = bt_addalias(av, i, &(*alias));
		else
			bt_showalias(av, i, alias);
		++i;
	}
	return (0);
}
