/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formats_parameter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 11:12:26 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/28 11:33:34 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

/*
** return parameter si existe sinon word
*/

char	*parameter_moins(char *parameter, char *word)
{
	char	*src;

	src = value_line_path(parameter, 0);
	if (!src)
		src = ft_strdup(word);
	return (src);
}

/*
** si parameter non initialiser alors donner valeur word et return
** valeur de parameter
*/

char	*parameter_equals(char *parameter, char *word)
{
	char	*src;

	src = value_line_path(parameter, 0);
	if (!src)
	{
		add_set_value(parameter, word);
		src = ft_strdup(word);
	}
	return (src);
}

/*
** si parameter est initialise return sinon parameter a null et
** affiche message d’erreur
*/

char	*parameter_interrogation(char *parameter, char *word)
{
	char	*src;

	src = value_line_path(parameter, 0);
	if (!src)
	{
		ft_dprintf(2, "42sh: %s: %s\n", parameter, word);
		src = NULL;
	}
	return (src);
}

/*
** si parameter existe et a deja une valeur,
** remplace ca valeur par word
*/

char	*parameter_plus(char *parameter, char *word)
{
	char	*src;

	src = value_line_path(parameter, 0);
	if (src && ft_strequ(src, "") == 0)
	{
		ft_strdel(&src);
		add_set_value(parameter, word);
		src = ft_strdup(word);
	}
	return (src);
}

/*
** ft_strlen(parameter)
*/

char	*parameter_hash_first(char *parameter)
{
	int		len;
	char	*src;

	len = 0;
	src = value_line_path(parameter, 0);
	if (src)
	{
		len = ft_strlen(src);
		ft_strdel(&src);
	}
	src = ft_itoa(len);
	return (src);
}

/*
** diff entre parameter et word affiche parameter. ex: salut#ok > salut ;
** salut#sal > ut ; salut#salut > ; salut#salutoi > salut
*/

char	*parameter_hash_end(char *value)
{
	char	*parameter;
	char	*dst;
	char	*stock;
	int		index;
	int		i;

	index = ft_chr_index(value, '#');
	stock = ft_strsub(value, 0, index);
	parameter = value_line_path(stock, 0);
	ft_strdel(&stock);
	if (!parameter)
		return (NULL);
	index += value[index + 1] && value[index + 1] == '#' ? 2 : 1;
	stock = value[index] ? search_var(value + index) : NULL;
	i = -1;
	if ((!stock) || ft_strlen(parameter) < ft_strlen(stock))
		i = 0;
	else
		while (parameter[++i] && stock[i])
			if (parameter[i] != stock[i])
				break ;
	dst = ft_strsub(parameter, i, ft_strlen(parameter) - i);
	ft_strdel(&parameter);
	ft_strdel(&stock);
	return (dst);
}

/*
** comme # mais inverse. ex: salut#sal > salut ;
** salut#ut > sal ; salut#salut > ; salut#salutoi > salut
*/

char	*parameter_percents(char *value)
{
	char	*parameter;
	char	*dst;
	char	*stock;
	int		index;
	int		i;

	index = ft_chr_index(value, '%');
	stock = ft_strsub(value, 0, index);
	parameter = value_line_path(stock, 0);
	ft_strdel(&stock);
	if (!parameter)
		return (NULL);
	index += value[index + 1] && value[index + 1] == '%' ? 2 : 1;
	stock = value[index] ? search_var(value + index) : NULL;
	index = ft_strlen(parameter);
	i = ft_strlen(stock);
	if (i <= index)
		while (--index > -1 && --i > -1 && parameter[index] && stock[i])
			if (parameter[index] != stock[i])
				break ;
	dst = ft_strsub(parameter, 0, index + 1);
	ft_strdel(&parameter);
	ft_strdel(&stock);
	return (dst);
}
