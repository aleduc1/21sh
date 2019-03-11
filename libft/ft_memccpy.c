/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 21:53:57 by mbellaic          #+#    #+#             */
/*   Updated: 2017/01/28 20:44:08 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = -1;
	ptr = dst;
	while (n > ++i)
	{
		*(ptr + i) = *((unsigned char *)src + i);
		if (*(ptr + i) == (unsigned char)c)
			return (dst + i + 1);
	}
	return (NULL);
}
