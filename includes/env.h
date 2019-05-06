/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 13:33:53 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/07 00:18:14 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef LIST_H
#	define LIST_H

#include "sh21.h"
#include "parser.h"
#include "libft.h"
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

typedef struct		s_redirection
{
	int		in;
	int		out;
	int		error;
}					t_redirection;

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
}t_commands;

/*
** list_redirection.c
*/

t_redirection		*init_redirection(void);
t_redirection		*fill_redirection(t_token *t);
void				delete_redirection(t_redirection **r);

/*
** main.c
*/

int					gest_return(int verif);
int					is_builtin(char **cmd, t_lex *lex);
int					is_in_path(char ***command);
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
//int					edit_set_cmd(t_cmd *cmd, t_env **my_env);
//int					edit_setenv(t_cmd *cmd, t_env **my_env);
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

int		return_good_fd(t_lex *lex, int fd);
int     builtin_set(t_lex *lex);
int     builtin_env(t_lex *lex);

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

int					open_file_command(t_redir *redir, t_pos *pos);
int					close_file_command(t_lex *lex);

/*
** execute_command.c
*/

int     			add_process(char *(*cmd), t_token *lex, int *returns_code, t_redirection *r);
int					exec_fork(char **cmd, t_token *lex, t_redirection *r);
void				open_redirection(t_redirection *r);
void				close_redirection(t_env *my_env, int old_fd[3]);

/*
** list_commands.c
*/

t_commands			*init_commands(char **commands, int fd_stock[3]);
void				delete_commands(t_commands **cmds);

/*
** commands.c
*/

int		ft_simple_command(char **argv, t_token *lex);
//int		ft_pipe_double(t_cmd *cmds, t_env **my_env);
int		ft_pipe(char **argv, t_token *lex, int end_pipe);
//int		ft_ampersand(t_cmd *cmds, int num_process, t_env **my_env);
//int		ft_ampersand_double(t_cmd *cmds, t_env **my_env);


t_env		*get_env(int is_end);
#	endif
