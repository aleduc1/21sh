/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 10:31:02 by sbelondr          #+#    #+#             */
/*   Updated: 2019/04/08 11:12:45 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static void	copy_value(char *src, char **dst, int start, int end)
{
	char	*tmp;
	char	*stock;

	stock = ft_strsub(src, start, end - start);
	tmp = ft_strjoin(*dst, stock);
	ft_strdel(&(*dst));
	ft_strdel(&stock);
	(*dst) = ft_strdup(tmp);
	ft_strdel(&tmp);
}

static char	*manage_var(char *str, t_env *my_env)
{
	char	*final;

	final = value_line_path(my_env, str, 0);
	if (!final)
		final = NULL;
	return (final);
}

static int	apply_rules(char *src, char **dst, int index, t_env *my_env)
{
	int		i;
	char	*tmp;
	char	*stock;
	char	*final;

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
	stock = manage_var(tmp, my_env);
	ft_strdel(&tmp);
	final = ft_strjoin(*dst, stock);
	ft_strdel(&(*dst));
	(*dst) = ft_strdup(final);
	ft_strdel(&stock);
	ft_strdel(&final);
	return (i > -1 ? i : ft_strlen(src));
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
		if (src[i] == '$')
		{
			if (i != last)
				copy_value(src, &dst, last, i);
			i = apply_rules(src, &dst, i, my_env);
			last = i + 1;
		}
	}
	if (i != last)
		copy_value(src, &dst, last, i);
	return (dst);
}

t_arg		*parser_var(char **value, t_env *my_env)
{
	t_arg	*current;
	t_arg	*head;
	char	*tmp;
	int		i;

	i = -1;
	current = NULL;
	current = init_arg();
	head = current;
	while (value[++i])
	{
		tmp = search_var(value[i], my_env);
		current->key = ft_strdup(value[i]);
		current->value = ft_strdup(tmp);
		ft_strdel(&(value[i]));
		value[i] = ft_strdup(tmp);
		ft_strdel(&tmp);
		current->next = init_arg();
		current = current->next;
	}
	return (head);
}
