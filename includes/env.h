/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 13:33:53 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/17 14:20:01 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef ENV_H
#	define ENV_H

#include "sh21.h"
#include "parser.h"
#include "libft.h"
#include <curses.h>
#include <term.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
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
	int		fd_pipe;
}					t_redirection;

typedef struct		s_env
{
	char			*key;
	char			*value;
	int				see_env;
	struct s_env	*next;
}					t_env;

/*
** manage_variable.c
*/

char				*manage_var(char *str);
int					manage_home(char *src, char **dst, int index);
int					modify_dst(char *tmp, char **dst);

/*
** list_redirection.c
*/

t_redirection		*init_redirection(void);
t_redirection		*fill_redirection(t_token *t);
void				delete_redirection(t_redirection **r);

/*
** other_tools.c
*/

int					gest_return(int verif);
int					is_builtin(char **argv, t_redirection *r);
int					is_in_path(char ***command);
t_env				*get_env(int is_end, t_env *head);

/*
** parser_var.c
*/

void				parser_var(char ***value);

/*
** manage_env.c
*/

int					edit_setenv(char *key, char *value);
int					edit_export(char *key);
int					ft_unsetenv(char *key);
char				**create_list_env(t_env *my_env, int env);

/*
** manage_set.c
*/

int					edit_set(char *key, char *value);
int					ft_unset(char *key);
int					edit_set_command_env(char *str, t_env *my_env);

/*
** tools_env.c
*/

char				*value_line_path(char *key, int env);
int					create_new_line_env(t_env *my_env, char *key, char *value,
		int env);

/*
** builtin_env.c
*/

int					builtin_set(t_redirection *r);
int					builtin_env(t_redirection *r, char **argv);

/*
** builtin_cd.c
*/

int					builtin_cd(char **arguments);

/*
** builtin_cd_verif.c
*/

int					ft_lastchr(const char *s, int c);
void				check_arg(char **str);
void				error_cd(int code, char *str);

/*
** list_env.c
*/

t_env				*init_env(void);
t_env				*init_maillon_env(void);
void				init_variable(void);

/*
** free_env.c
*/

void				free_env(t_env **env);
int					free_maillon_env(char *key, int env);

/*
** manage_file.c
*/

int					open_file_command(t_redir *redir, t_pos *pos);
int					close_file_command(t_lex *lex, t_redirection **r);
int					file_exist(char *name);

/*
** execute_command.c
*/

int					add_process(char *(*cmd), int *returns_code,
		t_redirection *r);
int					exec_fork(char **cmd, t_redirection *r);
void				sighandler(int signum);
int					ft_simple_command_env(char **argv, t_redirection *r);

/*
** commands.c
*/

int					ft_simple_command(char **argv, t_token *lex);
int					ft_pipe_double(char **argv, t_token *token);
int					ft_ampersand(char **argv, t_token *token, int num_process);
int					ft_ampersand_double(char **argv, t_token *token);

/*
** commands_pipe.c
*/

int					ft_pipe(char **argv, t_token *lex, int end_pipe);
int					add_pipe_process(char **cmd, t_redirection *r);

/*
** manage_quote.c
*/

void				ft_remove_quote(char **str);
int					ft_apply_dquote(char ***value, int index);

#	endif
