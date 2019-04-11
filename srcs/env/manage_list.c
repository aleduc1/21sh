/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 10:50:50 by sbelondr          #+#    #+#             */
/*   Updated: 2019/04/11 15:28:32 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	find_var_ast(t_ast *ast, t_env **my_env)
{
	if (ast->l)
	{
		find_var_ast(ast->l, &(*my_env));
		search_good_exec(ast->r, &(*my_env));
	}
	else
		search_good_exec(ast, &(*my_env));
}

void	manage_list(t_ast *ast, t_env **my_env)
{
	find_var_ast(ast, &(*my_env));
	execute_command_ast(
}
