/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstflip.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 17:34:54 by aleduc            #+#    #+#             */
/*   Updated: 2017/11/13 18:37:01 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstflip(t_list *head)
{
	t_list	*new;
	t_list	*buffer;

	if (!head)
		return (NULL);
	if (!(new = ft_lstnew(head->content, head->content_size)))
		return (NULL);
	buffer = new;
	while (head->next != NULL)
	{
		head = head->next;
		if (!(buffer = ft_lstnew(head->content, head->content_size)))
			return (NULL);
		ft_lstadd(&new, buffer);
		buffer = NULL;
	}
	return (new);
}
