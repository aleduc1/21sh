/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 13:33:53 by sbelondr          #+#    #+#             */
/*   Updated: 2019/04/27 15:31:18 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef LIST_H
#	define LIST_H

#include "parser.h"
#include "../libft/includes/libft.h"
#include <curses.h>
#include <term.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

typedef struct		s_env
{
	char			*key;
	char			*value;
	int				see_env;
	struct s_env	*next;
}					t_env;

typedef struct		s_arg
{
	char			*key;
	char			*value;
	struct s_arg	*next;
}					t_arg;

typedef struct	s_commands
{
	char				**command;
	int					fd_stock[3];
	struct s_commands	*next;
}				t_commands;

/*
** main.c
*/

int					gest_return(int verif, t_env **my_env);
int					is_builtin(t_cmd *cmd, t_env **my_env);
int					is_in_path(char ***command, t_env *my_env);
char				**transfer_arg(t_arg *lst_arg);

/*
** find_var.c
*/

t_arg				*manage_arg_env(char **arg, t_env *my_env);

/*
** parser.c
*/

void				parser_var(char ***value, t_env *my_env);
void				debug_arg(t_arg *arg);

/*
** manage_env.c
*/

int					edit_set(t_arg *arg, t_env **my_env);
int					edit_set_cmd(t_cmd *cmd, t_env **my_env);
int					edit_setenv(t_cmd *cmd, t_env **my_env);
int					edit_export(char *key, t_env **my_env);
int					ft_unsetenv(char *key, t_env **my_env);
int					ft_unset(char *key, t_env **my_env);
char				**create_list_env(t_env *my_env, int env);

/*
** tools_env.c
*/

int					create_new_path(t_env *my_env, t_arg *arg, int env);
int					search_line_env(t_env *my_env, char *key, int env);
char				*value_line_path(t_env *my_env, char *key, int env);

/*
** builtin_env.c
*/

int     builtin_set(t_env **my_env, t_cmd *cmd);
int     builtin_env(t_env **my_env, t_cmd *cmd);

/*
** list_env.c
*/

t_env				*init_env(void);
void				free_env(t_env **env);
int					free_maillon_env(t_env **my_env, char *key, int env);
t_arg				*init_arg(void);
void				free_arg(t_arg **lst_arg);
t_arg				*create_arg(char *key, char *value);
t_env				*init_maillon_env(void);

/*
** manage_file.c
*/

int					open_file_not_env(char *name, int end_line);
int					dest_output(t_env **my_env);
int					dest_error_output(t_env **my_env);
void				close_file(t_env **my_env);
void				close_error_file(t_env **my_env);

/*
** execute_command.c
*/

int     			add_process(t_cmd *cmd, t_env *my_env, int *returns_code);
int					exec_fork(t_cmd *cmd, t_env **my_env);
void				open_redirection(t_cmd *cmd);
void				close_redirection(t_env *my_env, int old_fd[3]);

/*
** list_commands.c
*/

t_commands			*init_commands(char **commands, int fd_stock[3]);
void				delete_commands(t_commands **cmds);

/*
** manage_list.c
*/

int		ft_simple_command(t_cmd *cmd, t_env **my_env);
int		ft_pipe_double(t_cmd *cmds, t_env **my_env);
int		ft_pipe(t_cmd *cmds, int nb, t_env **my_env);
int		ft_ampersand(t_cmd *cmds, int num_process, t_env **my_env);
int		ft_ampersand_double(t_cmd *cmds, t_env **my_env);

#	endif
