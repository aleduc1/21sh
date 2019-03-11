/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 18:36:32 by mbellaic          #+#    #+#             */
/*   Updated: 2017/01/28 21:12:16 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*ptr;

	i = 0;
	if (!s || !(ptr = ft_strnew(len)))
		return (NULL);
	while (len > i)
		*(ptr + i++) = *(s + start++);
	*(ptr + i) = '\0';
	return (ptr);
}
