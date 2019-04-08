/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formats_parameter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 11:12:26 by sbelondr          #+#    #+#             */
/*   Updated: 2019/04/08 11:11:47 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

/*
** return parameter si existe sinon word
*/

char	*parameter_moins(char *parameter, char *word, t_env *my_env)
{
	char	*src;

	src = value_line_path(my_env, parameter, 0);
	if (!src)
		return (word);
	else
		return (src);
}

/*
** si parameter non initialiser alors donner valeur word et return
** value de parameter
*/

char	*parameter_equals(char *parameter, char *word, t_env **my_env)
{
	t_arg	*arg;
	char	*src;

	src = value_line_path(*my_env, parameter, 0);
	if (!src)
	{
		arg = create_arg(parameter, word);
		edit_set(&(*my_env), arg);
		src = ft_strdup(arg->value);
		free_arg(&arg);
	}
	return (src);
}

/*
** si parameter est initialise return sinon parameter a null et
** affiche message d’erreur
*/

char	*parameter_interrogation(char *parameter, char *word, t_env **my_env)
{
	t_arg	*arg;
	char	*src;

	src = value_line_path(*my_env, parameter, 0);
	if (!src)
	{
		ft_dprintf(2, "minishell: %s: %s\n", parameter, word);
		arg = create_arg(parameter, NULL);
		edit_set(&(*my_env), arg);
		src = NULL;
		free_arg(&arg);
	}
	return (src);
}

/*
** ft_strlen(parameter)
*/

int		parameter_hash_first(char *parameter, t_env *my_env)
{
	int		len;
	char	*src;

	len = 0;
	src = value_line_path(my_env, parameter, 0);
	if (src)
	{
		len = ft_strlen(src);
		ft_strdel(&src);
	}
	return (len);
}

/*
** diff entre parameter et word affiche parameter. ex: salut#ok > salut ;
** salut#sal > ut ; salut#salut > ; salut#salutoi > salut |
** parameter var & word mot ou var (pour var $var)
*/

char	*parameter_hash_end(char *parameter, char *word)
{
	char	*dst;

	dst = ft_strstr(parameter, word);
	return (dst);
}

/*
** je sais pas
*/

char	*parameter_percents();
