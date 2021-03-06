/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_last.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 10:50:50 by sbelondr          #+#    #+#             */
/*   Updated: 2019/06/16 16:56:38 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

int	check_last_command(void)
{
	char	*str;
	int		check;

	str = value_line_path("?", 0);
	check = ft_atoi(str);
	ft_strdel(&str);
	return (check);
}

int	check_is_exec(char *src, t_redirection *r)
{
	char	*str;

	if (ft_strequ(src, "env") || ft_strequ(src, "set")
		|| ft_strequ(src, "setenv") || ft_strequ(src, "unsetenv")
		|| ft_strequ(src, "export") || ft_strequ(src, "unset")
		|| ft_strequ(src, "exit") || ft_strequ(src, "editset")
		|| ft_strequ(src, "echo") || ft_strequ(src, "cd"))
		return (1);
	str = is_in_path(src);
	if (!str)
	{
		gest_return(gest_error_path(src, r));
		return (0);
	}
	ft_strdel(&str);
	return (1);
}
