/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_alias_stillutils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 14:48:20 by apruvost          #+#    #+#             */
/*   Updated: 2019/06/11 15:40:37 by apruvost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ht_alias_table_null(t_alias **alias, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		alias[i] = NULL;
		++i;
	}
}

void	ht_alias_resize_up(t_ht_alias *ht)
{
	int	new_size;

	new_size = ht->base_size * 2;
	ht_alias_resize(ht, new_size);
}

void	ht_alias_resize_down(t_ht_alias *ht)
{
	int	new_size;

	new_size = ht->base_size / 2;
	ht_alias_resize(ht, new_size);
}