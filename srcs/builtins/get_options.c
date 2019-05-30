/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 03:17:29 by apruvost          #+#    #+#             */
/*   Updated: 2019/05/30 17:41:10 by apruvost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int			g_optind = 1;
int			g_opterr = 1;
int			g_optopt = 0;
char		g_optarg = NULL;

int			ft_getopt(int ac, char *const *av, const char *optstr)
{
	static char	*nextchar = NULL;

	if (av[g_optind] == NULL)
		return (-1);
}
