/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 17:36:44 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/08 03:50:17 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void		reset_pos(t_pos *pos)
{
	pos->historycount = 0;
	pos->historysum = 0;
	pos->nblines = 0;
	pos->currentline = 0;
	pos->selection = 0;
	pos->selectcount = 0;
	pos->inputlen = 0;
	pos->savecolumn = 0;
	pos->saverow = 0;
	pos->startrow = 0;
	pos->startcolumn = 0;
	pos->tailcolumn = 0;
	pos->tailrow = 0;
	pos->stop = 0;
}

int		builtin_env_display(t_redirection *r)
{
	int		i;
	char	**lst_env;

	i = -1;
	lst_env = create_list_env(get_env(0), 1);
	while (lst_env[++i])
		ft_dprintf(r->out, "%s\n", lst_env[i]);
	if (i == 0)
		ft_dprintf(r->error, "You are nothing value in env\n");
	ft_arraydel(&lst_env);
	return (0);
}

t_env	*copy_env(t_env *default_env)
{
	t_env	*new_env;
	t_env	*head;

	new_env = init_maillon_env();
	head = new_env;
	while (default_env->next)
	{
		new_env->key = ft_strdup(default_env->key);
		new_env->value = ft_strdup(default_env->value);
		new_env->see_env = default_env->see_env;
		new_env->next = init_maillon_env();
		default_env = default_env->next;
		if (default_env->next)
			new_env = new_env->next;
	}
	ft_printf("================= fin =============\n");
	new_env = head;
	return (new_env);
}

void	builtin_env_command(char **argv, t_redirection *r)
{
	edit_setenv("salut", "toi");
	builtin_env_display(r);
}

int		builtin_env(t_redirection *r, char **argv)
{
	int		verif;
	t_env	*default_env;
	t_env	*edit_df_env;

	verif = 0;
	default_env = get_env(0);
	if (ft_arraylen(argv) == 1)
		verif = builtin_env_display(r);
	else
	{
		edit_df_env = get_env(0);
		default_env = copy_env(edit_df_env);
		builtin_env_command(argv, r);
	ft_printf("================= 1 =============\n");
		edit_df_env = get_env(0);
	ft_printf("================= 2 =============\n");
		free_env(&edit_df_env);
	ft_printf("================= 3 =============\n");
		edit_df_env = copy_env(default_env);
	ft_printf("================= 4 =============\n");
	builtin_env_display(r);
	exit(0);
	}
	return (verif);
}

int		builtin_set(t_redirection *r)
{
	int		i;
	char	**lst_env;

	lst_env = create_list_env(get_env(0), 0);
	i = -1;
	while (lst_env[++i])
		ft_dprintf(r->out, "%s\n", lst_env[i]);
	if (i == 0)
		ft_dprintf(r->error, "You are nothing value in env\n");
	ft_arraydel(&lst_env);
	return (0);
}
