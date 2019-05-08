/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_commands.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 17:36:44 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/08 15:26:56 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static char	*manip_command_env(char ***input, int index)
{
	char	*str;
	char	*tmp;
	char	*stock;

	if (!((*input)[index]))
		return (NULL);
	str = ft_strdup((*input)[index]);
	while ((*input)[++index])
	{
		stock = ft_strjoin(" ", (*input)[index]);
		tmp = ft_strjoin(str, stock);
		ft_strdel(&stock);
		ft_strdel(&str);
		str = ft_strdup(tmp);
		ft_strdel(&tmp);
	}
	return (str);
}

static int	fuck_env(char **input, char **final)
{
	int		i;
	char	**str;

	i = 0;
	while (input[++i])
	{
		if (ft_strchr_exist(input[i], '='))
		{
			str = ft_strsplit(input[i], '=');
			edit_set_command_env(str[0], str[1]);
			ft_arraydel(&str);
		}
		else
		{
			if (ft_strchr_exist(input[i], '<') ||
						ft_strchr_exist(input[i], '>'))
				return (0);
			break ;
		}
	}
	(*final) = manip_command_env(&input, i);
	return (1);
}

int			check_is_env_command(char **input)
{
	char	*final;
	char	**str;
	int		verif;

	final = NULL;
	str = ft_strsplit(*input, 0);
	if ((!str) || ft_strequ(str[0], "env") == 0 || (!str[1]))
	{
		ft_arraydel(&str);
		return (0);
	}
	verif = fuck_env(str, &final);
	if (verif == 1)
	{
		ft_strdel(&(*input));
		(*input) = final;
	}
	ft_arraydel(&str);
	return (1);
}

/*
** separer le mallon avant delete
*/

void		check_delete_env_command(void)
{
	t_env	*my_env;
	t_env	*head;

	my_env = get_env(0, NULL);
	head = NULL;
	if (my_env && my_env->see_env == 3)
	{
		head = my_env->next;
		ft_strdel(&(my_env->key));
		ft_strdel(&(my_env->value));
		free(my_env);
		get_env(0, head);
	}
}
