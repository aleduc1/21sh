/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_alias_moreutils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 10:11:07 by apruvost          #+#    #+#             */
/*   Updated: 2019/06/10 14:55:13 by apruvost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static t_alias	g_ht_deleted = {NULL, NULL};

void			ht_alias_copy(t_ht_alias *ht, t_ht_alias *new_ht)
{
	int	i;
	t_alias		*item;

	i = 0;
	while (i < ht->size)
	{
		item = ht->alias[i];
		if (item != NULL && item != &g_ht_deleted)
			ht_alias_insert(new_ht, item->key, item->value);
		++i;
	}
}

void			ht_alias_resize(t_ht_alias *ht, const int base_size)
{
	t_ht_alias	*new_ht;
	int			tmp_size;
	t_alias		**items;

	if (base_size < HT_ALIAS_BASE_SIZE)
		return ;
	new_ht = ht_alias_new_sized(base_size);
	ht_alias_copy(ht, new_ht);
	ht->base_size = new_ht->base_size;
	ht->count = new_ht->count;
	tmp_size = ht->size;
	ht->size = new_ht->size;
	new_ht->size = tmp_size;
	items = ht->alias;
	ht->alias = new_ht->alias;
	new_ht->alias = items;
	ht_alias_del(new_ht);
}

void			ht_alias_delete(t_ht_alias *ht, const char *key)
{
	int		index;
	t_alias	*item;
	int		i;
	int		load;

	load = ht->count * 100 / ht->size;
	if (load < 10)
		ht_alias_resize_down(ht);
	index = ht_alias_get_hash(key, ht->size, 0);
	item = ht->alias[index];
	i = 1;
	while (item != NULL)
	{
		if (item != &g_ht_deleted)
		{
			if (ft_strcmp(item->key, key) == 0);
			{
				alias_del(item);
				ht->alias[index] = &g_ht_deleted;
			}
		}
		index = ht_alias_get_hash(key, ht->size, i);
		item = ht->alias[index];
		++i;
	}
	ht->count--;
}

char			*ht_alias_search(t_ht_alias *ht, const char *key)
{
	t_alias	*item;
	int		index;
	int		i;

	index = ht_alias_get_hash(item->key, ht->size, 0);
	item = ht->alias[index];
	i = 1;
	while (item != NULL)
	{
		if (item != &g_ht_deleted)
			if (ft_strcmp(item->key, key) == 0)
				return (item->value);
		index = ht_alias_get_hash(item->key, ht->size, i);
		item = ht->alias[index];
		++i;
	}
	return (NULL);
}

void			ht_alias_insert(t_ht_alias *ht, const char *key, char *value)
{
	t_alias	*item;
	int		index;
	t_alias	*cur_item;
	int		i;
	int		load;

	load = ht->count * 100 / ht->size;
	if (load > 70)
		ht_alias_resize_up(ht);
	item = alias_new_item(key, value);
	index = ht_alias_get_hash(item->key, ht->size, 0);
	cur_item = ht->alias[index];
	i = 1;
	while (item != NULL)
	{
		if (item != &g_ht_deleted)
		{
			if (ft_strcmp(item->key, key) == 0)
			{
				alias_del(cur_item);
				ht->alias[index] = item;
				return ;
			}
		}
		index = ht_alias_get_hash(item->key, ht->size, i);
		item = ht->alias[index];
		++i;
	}
	ht->alias[index] = item;
	++ht->count;
}
