/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 13:33:53 by sbelondr          #+#    #+#             */
/*   Updated: 2019/06/15 19:03:25 by mbellaic         ###   ########.fr       */
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

typedef struct		s_redirect
{
	int					base;
	int					new_fd;
	struct s_redirect	*next;
}					t_redirect;

typedef struct		s_redirection
{
	int			in;
	int			out;
	int			error;
	int			fd_pipe;
	t_redirect	*redirect;
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

/*
** delete_redirection.c
*/

void				delete_redirection(t_redirection **r);
int					verif_close(int fd);

/*
** other_tools.c
*/

int					gest_return(int verif);
int					is_builtin(char **argv, t_redirection *r);
char				*is_in_path(char *command);
t_env				*get_env(int is_end, t_env *head);

/*
** parser_var.c
*/

void				parser_var(char ***value);
void				parser_var_simple(char **value);
char				*search_var(char *src, int is_quote);

/*
** apply_parser_var.c
*/

int					apply_rules(char *src, char **dst, int index);

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

int					edit_set(char **value);
int					ft_unset(char *key);
int					edit_set_command_env(char *str, t_env *my_env);
int					add_set_value(char *key, char *value);

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

int					builtin_cd(char **arguments, t_redirection *r);

/*
** builtin_cd_verif.c
*/

int					ft_lastchr(const char *s, int c);
void				check_arg(char **str, t_redirection *r);
void				error_cd(int code, char *str, t_redirection *r);

/*
** list_env.c
*/

t_env				*init_env(void);
t_env				*init_maillon_env(void);
void				init_variable(void);
t_env				*ft_cpy_env(void);

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
int					file_exist(char *name, int type);

/*
** manage_quote.c
*/

void				ft_remove_quote(char **str);
int					ft_apply_dquote(char ***value, int index);

/*
** list_redirect.c
*/

int					ft_create_maillon_redirect(t_redirect *r, int base,
						int new_fd);
t_redirect			*ft_init_redirect(void);
int					ft_fd_redirect_exist(t_redirect *r, int base);

/*
** signal.c
*/

void				sighandler(int signum);
void				sig_handler(void);
void				sig_dfl(void);
void				sig_ign(void);

/*
** formats_parameter.c
*/

char				*parameter_hash_first(char *parameter);
char				*parameter_hash_end(char *value);
char				*parameter_percents(char *value);

/*
** formats_parameter_bis.c
*/

char				*parameter_moins(char *parameter, char *word);
char				*parameter_equals(char *parameter, char *word);
char				*parameter_interrogation(char *parameter, char *word);
char				*parameter_plus(char *parameter, char *word);

/*
** parameter_expansion.c
*/

void				parameter_expansion(char *tmp, char **dst);

/*
** check_last.c
*/

int					check_last_command(void);
int					check_is_exec(char *src, t_redirection *r);

/*
** tools_setenv.c
*/

int					str_is_alpha(char *str);
int					is_correct_setenv(char c);
void				setenv_error(void);

/*
** test_quote.c
*/

int					test_quote(char *name);

/*
** gest_error_exec.c
*/

int					gest_error_path(char *cmd, t_redirection *r);
void				gest_error_exec(char *cmd, t_redirection *r);

#	endif
