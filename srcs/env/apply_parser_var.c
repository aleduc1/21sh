/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_parser_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 10:31:02 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/28 09:57:34 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static int	is_special_parameters(char c)
{
	if (c == '#' || c == '?' || c == '-' || c == '$' || c == '!' || c == '0')
		return (1);
	return (0);
}

static int	ft_chr_index_last(char *str, char c, char d)
{
	int		i;
	int		not_end;
	int		index;

	i = -1;
	index = 0;
	not_end = 1;
	while (str[++i])
	{
		if (str[i] == c)
			++not_end;
		else if (str[i] == d)
		{
			--not_end;
			index = i;
			if (not_end < 1)
				break ;
		}
	}
	return (index);
}

static int	apply_simple_var(int index, char *src, char **dst)
{
	char	*tmp;
	int		i;

	i = index;
	while (src[++i])
		if ((ft_isalnum(src[i]) == 0 && src[i] != '_'))
		{
			if (i == index + 1 && is_special_parameters(src[i]))
				++i;
			break ;
		}
	--i;
	tmp = ft_strsub(src, index + 1, i - index);
	modify_dst(tmp, dst);
	ft_strdel(&tmp);
	return (i);
}

int			apply_rules(char *src, char **dst, int index)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	if (src[index + 1] == '{')
	{
		index += 2;
		i = ft_chr_index_last(src + index, '{', '}');
		tmp = ft_strsub(src + index, 0, i);
		i += index;
		parameter_expansion(tmp, dst);
	}
	else
		i = apply_simple_var(index, src, dst);
	ft_strdel(&tmp);
	if (i < 0)
		i = ft_strlen(src);
	return (i);
}
