/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_commands.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 17:36:44 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/09 05:22:59 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

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
