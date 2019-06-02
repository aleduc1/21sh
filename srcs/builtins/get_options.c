/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 03:17:29 by apruvost          #+#    #+#             */
/*   Updated: 2019/05/31 04:31:12 by apruvost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int			ft_getopt(char *str, t_cd *cd)
{
	if (ft_strequ(str, "-L"))
	{
		cd->arg_L = 1;
		cd->arg_P = 0;
	}
	else if (ft_strequ(str, "-P"))
	{
		cd->arg_L = 0;
		cd->arg_P = 1;
	}
	else if (ft_strequ(str, "--"))
		return (3);
	else if (str[0] == '-' && str[1])
	{
		ft_dprintf(2, "%s: invalid option\n", str[1]);
		ft_dprintf(2, "cd: usage: cd [-L|-P] [dir]\n");
		return (0);
	}
	else
		return (2);
	return (1);
}
