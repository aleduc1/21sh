/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 23:25:43 by mbellaic          #+#    #+#             */
/*   Updated: 2018/10/31 13:40:44 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*rslt;

	if (!(rslt = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	if (content == NULL)
	{
		rslt->content = NULL;
		rslt->content_size = 0;
	}
	else
	{
		if (!(rslt->content = (void*)malloc(content_size)))
			return (NULL);
		ft_memcpy(rslt->content, content, content_size);
		rslt->content_size = content_size;
	}
	rslt->next = NULL;
	return (rslt);
}
