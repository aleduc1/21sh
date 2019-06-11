/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 15:17:51 by apruvost          #+#    #+#             */
/*   Updated: 2019/06/11 16:46:12 by apruvost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	alias_del(t_alias *alias)
{
	free(alias->key);
	alias->key = NULL;
	free(alias->value);
	alias->key = NULL;
}

t_alias	*alias_new_item(const char *k, const char *v)  // PROTECT MALLOC CAREFUL
{
	t_alias	*item;
	
	item = (t_alias *)malloc(sizeof(t_alias));
	item->key = ft_strdup(k);
	item->value = ft_strdup(v);
	return (item);
}
