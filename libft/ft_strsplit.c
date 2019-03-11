/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 18:36:11 by mbellaic          #+#    #+#             */
/*   Updated: 2019/02/07 18:18:22 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		g_len;

char		**ft_strsplit(const char *s, char c)
{
	char	**ret;
	size_t	i;
	size_t	j;

	if (!s || !c)
		return (0);
	if (!(ret = ft_memalloc(ft_strlen(s) + 1)))
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			g_len = 0;
			while (s[i + g_len] && (s[i + g_len] != c))
				g_len++;
			ret[j++] = ft_strsub(s, i, g_len);
			i = i + g_len;
		}
	}
	ret[j] = 0;
	return (ret);
}
