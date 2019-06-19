/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 13:33:53 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/19 13:39:30 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef COMMANDS_H
#	define COMMANDS_H

#include "env.h"

/*
** execute_command.c
*/

int					add_process(char *(*cmd), int *returns_code,
		t_redirection *r);
int					exec_fork(char **cmd, t_redirection *r);
void				sighandler(int signum);
int					ft_simple_command_env(char **argv, t_redirection *r);
int					gest_error_path(char *cmd, t_redirection *r);

/*
** commands.c
*/

int					ft_simple_command(char **argv, t_token *lex);
int					ft_pipe_double(char **argv, t_token *token);
int					ft_ampersand(char **argv, t_token *token, int num_process);
int					ft_ampersand_double(char **argv, t_token *token);
int					check_last_command(void);

/*
** commands_pipe.c
*/

int					ft_pipe(char **argv, t_token *lex, int end_pipe);
int					add_pipe_process(char **cmd, t_redirection *r);

/*
** redirection.c
*/

void				redirection_fd(t_redirection *r);

#	endif
