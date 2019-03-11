/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 23:20:46 by mbellaic          #+#    #+#             */
/*   Updated: 2018/10/31 13:40:13 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*node;

	node = NULL;
	if (lst && f)
	{
		node = f(lst);
		node->next = lst->next ? ft_lstmap(lst->next, f) : NULL;
	}
	return (node);
}
