/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 19:40:43 by mbellaic          #+#    #+#             */
/*   Updated: 2017/01/29 20:47:18 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*str;

	if (!(str = (void*)malloc(sizeof(void*) * size + 1)))
		return (NULL);
	if (str == NULL)
		return (NULL);
	ft_bzero(str, size);
	return (str);
}
