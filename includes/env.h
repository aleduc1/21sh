/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 13:33:53 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/08 01:02:43 by apruvost         ###   ########.fr       */
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
int					is_builtin(char **argv, t_redirection *r);
int					is_in_path(char ***command);

/*
** parser.c
*/

void				parser_var(char ***value);

/*
** manage_env.c
*/

int					edit_set(char *key, char *value);
int					edit_setenv(char *key, char *value);
int					edit_export(char *key);
int					ft_unsetenv(char *key);
int					ft_unset(char *key);
char				**create_list_env(t_env *my_env, int env);

/*
** tools_env.c
*/

int					is_env_empty(char *key);
int					create_new_path(t_env *my_env, char *key, char *value, int env);
int					search_line_env(t_env *my_env, char *key, int env);
char				*value_line_path(char *key, int env);

/*
** builtin_env.c
*/

int		return_good_fd(t_lex *lex, int fd);
int     builtin_set(t_redirection *r);
int     builtin_env(t_redirection *r);

/*
** list_env.c
*/

t_env				*init_env(void);
void				free_env(t_env **env);
int					free_maillon_env(char *key, int env);
t_env				*init_maillon_env(void);
void				init_variable(void);

/*
** manage_file.c
*/

int					open_file_command(t_redir *redir, t_pos *pos);
int					close_file_command(t_lex *lex, t_redirection **r);
int					file_exist(char *name);

/*
** execute_command.c
*/

int     			add_process(char *(*cmd), int *returns_code, t_redirection *r);
int					exec_fork(char **cmd, t_redirection *r);
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
int		ft_pipe(char **argv, t_token *lex, int end_pipe);
int		ft_pipe_double(char **argv, t_token *token);
int		ft_ampersand(char **argv, t_token *token, int num_process);
int		ft_ampersand_double(char **argv, t_token *token);


t_env		*get_env(int is_end);
#	endif
