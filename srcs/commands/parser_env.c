/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 10:31:02 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/07 23:37:54 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/env.h"

static void	copy_value(char *src, char **dst, int start, int end)
{
	char	*tmp;
	char	*stock;

	stock = ft_strsub(src, start, end - start);
	tmp = ft_strjoin(*dst, stock);
	ft_strdel(&(*dst));
	ft_strdel(&stock);
	(*dst) = tmp ? ft_strdup(tmp) : NULL;
	ft_strdel(&tmp);
}

static char	*manage_var(char *str)
{
	char	*final;

	final = value_line_path(str, 0);
	if (!final)
		final = ft_strdup("");
	return (final);
}

static int	manage_home(char **dst, int index, t_env *my_env)
{
	char	*data;

	index += 1;
	data = manage_var("HOME");
	ft_strdel(&(*dst));
	(*dst) = ft_strdup(data);
	return (index);
}

static int	modify_dst(char *tmp, t_env *my_env, char **dst)
{
	char	*stock;
	char	*final;

	stock = manage_var(tmp);
	ft_strdel(&tmp);
	final = ft_strjoin(*dst, stock);
	ft_strdel(&(*dst));
	if (final)
		(*dst) = ft_strdup(final);
	else
		(*dst) = NULL;
	ft_strdel(&stock);
	ft_strdel(&final);
	return (0);
}

static int	apply_rules(char *src, char **dst, int index, t_env *my_env)
{
	int		i;
	char	*tmp;

	if (src[index + 1] == '{')
	{
		i = ft_chr_index(src + index, '}') + index;
		tmp = ft_strsub(src, index + 2, i - index - 2);
	}
	else
	{
		i = ft_chr_index(src + index + 1, '$');
		if (i > -1)
		{
			i += index;
			tmp = ft_strsub(src, index + 1, i - index);
		}
		else
			tmp = ft_strsub(src, index + 1, ft_strlen(src));
	}
	modify_dst(tmp, my_env, &(*dst));
	if (i < 0)
		i = ft_strlen(src);
	return (i);
}

static char	*search_var(char *src, t_env *my_env)
{
	int		i;
	int		len;
	int		last;
	char	*dst;

	i = -1;
	last = 0;
	len = ft_strlen(src);
	dst = ft_strdup("");
	while (++i < len)
	{
		if (src[i] == '$' || (i == 0 && src[i] == '~'))
		{
			if (i != last)
				copy_value(src, &dst, last, i);
			if (src[i] == '~')
				i = manage_home(&dst, i, my_env) - 1;
			else
				i = apply_rules(src, &dst, i, my_env);
			last = i + 1;
		}
	}
	if (i != last)
		copy_value(src, &dst, last, i);
	return (dst);
}

void		parser_var(char ***value)
{
	t_env	*my_env;
	char	*tmp;
	int		i;

	i = -1;
	my_env = get_env(0);
	while ((*value)[++i])
	{
		if (ft_strchr_exist((*value)[i], '$') ||
				(*value)[i][0] == '~')
		{
			tmp = search_var((*value)[i], my_env);
			ft_strdel(&((*value)[i]));
			(*value)[i] = tmp ? ft_strdup(tmp) : NULL;
			ft_strdel(&tmp);
		}
	}
}
