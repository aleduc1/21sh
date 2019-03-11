/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 21:13:07 by mbellaic          #+#    #+#             */
/*   Updated: 2017/01/30 00:57:05 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*src;
	char			*dst;
	size_t			i;

	src = (char *)s;
	if (src && f)
	{
		if (!(dst = ft_strnew(ft_strlen(s))))
			return (NULL);
		i = 0;
		while (src[i] != '\0')
		{
			dst[i] = (*f)(i, src[i]);
			i++;
		}
		return (dst);
	}
	return (NULL);
}
