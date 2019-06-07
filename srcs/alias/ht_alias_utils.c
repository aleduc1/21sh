/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_alias_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 16:10:12 by apruvost          #+#    #+#             */
/*   Updated: 2019/06/07 16:35:57 by apruvost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void		ht_alias_del(t_ht_alias *ht)
{
	int		i;
	t_alias	*item;

	i = 0;
	while (i < ht->size)
	{
		item = ht->alias[i];
		if (item != NULL)
			alias_del(item);
		++i;
	}
	ft_memdel(&(ht->alias));
	ft_memdel(&ht);
}

t_ht_alias	*ht_alias_new(void)		// PRETOECT MALLOC CAREFUL
{
	t_ht_alias	*ht;

	ht = (t_ht_alias *)malloc(sizeof(t_ht_alias));
	ht->size = 53;
	ht->count = 0;
	ht->alias = (t_alias **)malloc(sizeof(t_alias*));
	ft_alias_table_null(ht->alias, ht->size);
	retur (ht);
}
