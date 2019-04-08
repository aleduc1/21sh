/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_s.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 07:11:11 by sbelondr          #+#    #+#             */
/*   Updated: 2019/04/08 10:47:51 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

void	ft_arg_s(t_printf **lst)
{
	char	*str;

	if (!(str = ft_strdup(va_arg((*lst)->ap, char*))))
		str = ft_strdup("(null)");
	apply_arg_s(str, &(*lst));
	ft_strdel(&str);
}

void	ft_arg_c(t_printf **lst)
{
	char	c;

	if (!(c = (char)(va_arg((*lst)->ap, int))))
	{
		(*lst)->len += 1;
		apply_arg_c(0, &(*lst));
	}
	else
		apply_arg_c(c, &(*lst));
}

void	ft_arg_percent(t_printf **lst)
{
	char	c;

	c = '%';
	apply_arg_c(c, &(*lst));
}
