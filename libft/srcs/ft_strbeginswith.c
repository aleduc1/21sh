/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strbeginswith.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 12:40:11 by aleduc            #+#    #+#             */
/*   Updated: 2018/09/15 14:30:19 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strbeginswith(const char *string, char *prefix)
{
	size_t prefix_len;

	if (!string || !prefix)
		return (-1);
	prefix_len = ft_strlen(prefix);
	return (ft_strnequ(string, prefix, prefix_len));
}
