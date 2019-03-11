/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 19:12:57 by mbellaic          #+#    #+#             */
/*   Updated: 2019/02/03 07:17:45 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char		*ft_strdup(char *src)
{
	int		i;
	int		src_size;
	char	*new_str;

	i = 0;
	src_size = 0;
	while (src[src_size])
		src_size++;
	new_str = (char*)malloc(sizeof(*new_str) * (src_size) + 1);
	if (new_str == NULL)
		return (NULL);
	while (i < src_size)
	{
		new_str[i] = src[i];
		i++;
	}
	new_str[src_size] = '\0';
	return (new_str);
}
