/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 19:44:02 by mbellaic          #+#    #+#             */
/*   Updated: 2017/01/28 22:01:57 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int						ft_atoi(const char *str)
{
	unsigned long long	i;
	unsigned long long	ret;
	int					sign;

	i = 0;
	ret = 0;
	sign = 1;
	while ((*(str + i) == ' ') || (*(str + i) == '\f') ||
			(*(str + i) == '\n') || (*(str + i) == '\r') ||
			(*(str + i) == '\t') || (*(str + i) == '\v'))
		i++;
	if (*(str + i) == '-')
		sign = -1;
	if (*(str + i) == '+' || *(str + i) == '-')
		i++;
	while (ft_isdigit(*(str + i)))
	{
		ret = ret * 10 + (int)(*(str + i++) - '0');
		if (ret >= 9223372036854775807)
			return (sign == 1 ? -1 : 0);
	}
	return (sign * ret);
}
