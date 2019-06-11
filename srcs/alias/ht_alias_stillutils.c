/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_alias_stillutils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 14:48:20 by apruvost          #+#    #+#             */
/*   Updated: 2019/06/10 14:51:15 by apruvost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

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
