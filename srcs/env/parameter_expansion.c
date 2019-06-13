/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 12:02:28 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/28 11:14:59 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

/*
** split :
** find arg
** apply ft avec tableau de pointeur
*/

static char		*(**init_array(void))(char*, char*)
{
	char	*(**conv)(char*, char*);
	int		i;

	conv = ft_memalloc(255 * sizeof(void*));
	i = -1;
	while (++i <= 254)
		conv[i] = 0;
	conv['-'] = &parameter_moins;
	conv['='] = &parameter_equals;
	conv['?'] = &parameter_interrogation;
	conv['+'] = &parameter_plus;
	return (conv);
}

char			*gest_expansion(char *key, char *value)
{
	char	*(**conv)(char*, char*);
	char	*final;

	conv = init_array();
	final = NULL;
	if (conv[(int)value[0]])
		final = (*conv[(int)value[0]])(key, value + 1);
	free(conv);
	conv = NULL;
	return (final);
}

int				is_other_expansion(char *tmp, char **dst)
{
	if (tmp[0] == '#')
	{
		ft_strdel(dst);
		(*dst) = parameter_hash_first(tmp + 1);
	}
	else if (ft_chr_index(tmp, '#') > 0)
	{
		ft_strdel(dst);
		(*dst) = parameter_hash_end(tmp);
	}
	else if (ft_chr_index(tmp, '%') > 0)
	{
		ft_strdel(dst);
		(*dst) = parameter_percents(tmp);
	}
	else
		return (0);
	return (1);
}

void			parameter_expansion(char *tmp, char **dst)
{
	char	*key;
	int		i;

	if (!tmp)
		return ;
	i = ft_chr_index(tmp, ':');
	if (i < 2)
	{
		if (is_other_expansion(tmp, dst) == 0)
			modify_dst(tmp, dst);
	}
	else
	{
		key = ft_strsub(tmp, 0, i);
		ft_strdel(&(*dst));
		(*dst) = gest_expansion(key, tmp + i + 1);
		ft_strdel(&key);
	}
}
