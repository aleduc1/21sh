/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 18:36:52 by mbellaic          #+#    #+#             */
/*   Updated: 2017/01/30 01:14:20 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(const char *s)
{
	char	*str;
	size_t	len;

	if (!s)
		return (NULL);
	len = 0;
	while (*s == ' ' || *s == '\t' || *s == '\n')
		s += 1;
	len = (ft_strlen(s));
	while ((s[len - 1] == ' ' || s[len - 1] == '\t' || s[len - 1] == '\n')
			&& len)
		len--;
	if (!(str = (char*)malloc(len + 1)))
		return (NULL);
	str[len] = '\0';
	while (len)
	{
		len--;
		str[len] = s[len];
	}
	return (str);
}
