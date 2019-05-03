/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 12:49:50 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/03 13:10:12 by sbelondr         ###   ########.fr       */
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

void	print_cmd(t_cmd *cmd)
{
	ft_printf("in->fd %d, in->filename = %s, in->append = %d\n", cmd->in->fd,
			cmd->in->filename, cmd->in->append);
	ft_printf("out->fd %d, out->filename = %s, out->append = %d\n", cmd->out->fd,
			cmd->out->filename, cmd->out->append);
	ft_printf("err->fd %d, err->filename = %s, err->append = %d\n", cmd->err->fd,
			cmd->err->filename, cmd->err->append);
	ft_printf("**argv:\n");
	ft_arraydisplay(cmd->argv);
}

int		main(int ac, char **av)
{
	t_cmd	*cmd;
	char	*testa[2] = {"pwd", NULL};
	char	*testb[2] = {"set", NULL};
	t_env	*env;
	int		i;

	if (ac == -1)
		return (0);
	i = 0;
	env = init_env();

	cmd = init_cmd();
	cmd->argv = ft_arraydup(av + 1);
	cmd->out->fd = -1;
	cmd->out->append = 1;
	ft_strdel(&((cmd->out->filename)));
	cmd->out->filename = ft_strdup("coucou");
	open_file_std(cmd->out);

	parser_var(&(cmd->argv), env);
//	cmd->out->fd = open_file_not_env("test.txt", 0);

	cmd->next = init_cmd();
	cmd->next->argv = ft_arraydup(testb);
	parser_var(&(cmd->next->argv), env);
	
	cmd->next->next = init_cmd();
	cmd->next->next->argv = ft_arraydup(testa);
	parser_var(&(cmd->next->next->argv), env);
	
	i = ft_simple_command(cmd, &env);
	close_file_command(cmd);
//	i = ft_simple_command(cmd->next, &env);
//	i = ft_pipe(cmd, 3, &env);
//	i = ft_pipe_double(cmd, &env);
//	i = ft_ampersand(cmd, 1, &env);
//	i = ft_ampersand_double(cmd, &env);
	
	gest_return(i, &env);
	if (i == -1)
		ft_dprintf(2, "21sh: command not found: %s\n", cmd->argv[0]);

	free_cmd(&cmd);
	gest_return(i, &env);
	free_env(&env);
	return (0);
}
