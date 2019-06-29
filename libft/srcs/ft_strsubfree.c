/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsubfree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 11:42:12 by aleduc            #+#    #+#             */
/*   Updated: 2018/06/21 13:33:24 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsubfree(char *s, unsigned int start, size_t len)
{
	char *res;

	res = ft_strsub(s, start, len);
	free(s);
	return (res);
}
