/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 19:17:09 by mbellaic          #+#    #+#             */
/*   Updated: 2017/01/17 21:18:36 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dest, char *src, size_t size)
{
	char	*cur;
	char	*reader;
	size_t	len;

	cur = (char *)ft_memchr(dest, '\0', size);
	if (cur == NULL)
		return (size + ft_strlen(src));
	reader = (char *)src;
	len = (size_t)(cur - dest) + ft_strlen(reader);
	while ((size_t)(cur - dest) < size - 1 && *reader != '\0')
	{
		*cur = *reader;
		cur++;
		reader++;
	}
	*cur = '\0';
	return (len);
}
