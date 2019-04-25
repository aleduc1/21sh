/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 12:49:50 by sbelondr          #+#    #+#             */
/*   Updated: 2019/04/25 18:56:35 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/env.h"

void	free_std(t_std **std)
{
	if (std && (*std))
	{
		ft_strdel(&((*std)->filename));
		free(*std);
		(*std) = NULL;
	}
}

void	free_cmd(t_cmd **cmd)
{
	if ((!cmd) || (!(*cmd)))
		return ;
	if ((*cmd)->next)
		free_cmd(&((*cmd)->next));
	free_std(&((*cmd)->in));
	free_std(&((*cmd)->out));
	free_std(&((*cmd)->err));
	ft_arraydel(&((*cmd)->argv));
	ft_strdel(&((*cmd)->heredoc));
	free(*cmd);
	(*cmd) = NULL;
}

int		main(int ac, char **av)
{
	t_cmd	*cmd;
	char	*testa[2] = {"wc", NULL};
	char	*testb[3] = {"cat", "-e", NULL};
	t_env	*env;
	int		i;

	if (ac == -1)
		return (0);
	i = 0;
	env = init_env();
	
	cmd = init_cmd();
	cmd->argv = ft_arraydup(av + 1);
	parser_var(&(cmd->argv), env);

	cmd->next = init_cmd();
	cmd->next->argv = ft_arraydup(testb);
	parser_var(&(cmd->argv), env);
	
	cmd->next->next = init_cmd();
	cmd->next->next->argv = ft_arraydup(testa);
	parser_var(&(cmd->argv), env);
	
//	i = ft_simple_command(cmd, &env);
	i = ft_pipe(cmd, 3, &env);
//	i = ft_pipe_double(cmd, cmd->next, &env);
//	i = ft_ampersand(cmd, 2, &env);
//	i = ft_ampersand_double(cmd, cmd->next, &env);

	free_cmd(&cmd);
	gest_return(i, &env);
	free_env(&env);
	return (0);
}
