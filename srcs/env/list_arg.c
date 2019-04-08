/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 16:41:04 by sbelondr          #+#    #+#             */
/*   Updated: 2019/04/08 11:11:58 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

t_arg		*create_arg(char *key, char *value)
{
	t_arg	*arg;

	arg = init_arg();
	arg->key = ft_strdup(key);
	arg->value = ft_strdup(value);
	return (arg);
}

t_arg		*init_arg(void)
{
	t_arg	*lst_arg;

	if (!(lst_arg = (t_arg*)malloc(sizeof(t_arg) * 1)))
		return (NULL);
	lst_arg->key = NULL;
	lst_arg->value = NULL;
	lst_arg->next = NULL;
	return (lst_arg);
}

void		free_arg(t_arg **lst_arg)
{
	t_arg	*tmp;

	if ((!lst_arg) || (!(*lst_arg)))
		return ;
	while (*lst_arg)
	{
		tmp = *lst_arg;
		(*lst_arg) = (*lst_arg)->next;
		ft_strdel(&(tmp->key));
		ft_strdel(&(tmp->value));
		free(tmp);
		tmp = NULL;
	}
	free(*lst_arg);
	*lst_arg = NULL;
}
