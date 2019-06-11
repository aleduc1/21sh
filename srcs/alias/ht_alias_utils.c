/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_alias_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 16:10:12 by apruvost          #+#    #+#             */
/*   Updated: 2019/06/11 17:10:02 by apruvost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int			ht_alias_hash(const char *s, const int a, const int m)
{
	long	hash;
	int		len;
	int		i;

	hash = 0;
	len = 0;
	i = 0;
	len = ft_strlen(s);
	while (i < len)
	{
		hash += ft_lpow(a, len - (i + 1)) * s[i];
		hash = hash % m;
		++i;
	}
	return ((int)hash);
}

int			ht_alias_get_hash(const char *s, const int num, const int attempt)
{
	int		hash_a;
	int		hash_b;

	hash_a = ht_alias_hash(s, HT_ALIAS_HASH_ONE, num);
	hash_b = ht_alias_hash(s, HT_ALIAS_HASH_TWO, num);
	return ((hash_a + (attempt * (hash_b + 1))) % num);
}

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
	ft_memdel((void **)&(ht->alias));
	ft_memdel((void **)&ht);
}

t_ht_alias	*ht_alias_new_sized(const int base_size)   // PRETOECT MALLOC CAREFUL
{
	t_ht_alias	*ht;

	ht = (t_ht_alias *)malloc(sizeof(t_ht_alias));
	ht->base_size = base_size;
	ht->size = ft_nextprime(ht->base_size);
	ht->count = 0;
	ht->alias = (t_alias **)malloc(sizeof(t_alias*) * ht->size);
	ht_alias_table_null(ht->alias, ht->size);
	return (ht);
}

t_ht_alias	*ht_alias_new(void)
{
	return (ht_alias_new_sized(HT_ALIAS_BASE_SIZE));
}
