/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 13:33:53 by sbelondr          #+#    #+#             */
/*   Updated: 2019/04/08 09:24:18 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef LIST_H
#	define LIST_H

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

/*
** main.c
*/

int					gest_return(int verif, t_env **my_env);
int					is_builtin(t_arg *arg, t_env **my_env);
int					is_in_path(char ***command, t_env *my_env);
char				**transfer_arg(t_arg *lst_arg);

/*
** find_var.c
*/

t_arg				*manage_arg_env(char **arg, t_env *my_env);

/*
** parser.c
*/

t_arg				*parser_var(char **value, t_env *my_env);
void				debug_arg(t_arg *arg);

/*
** manage_env.c
*/

int					edit_set(t_env **my_env, t_arg *arg);
int					edit_setenv(t_env **my_env, t_arg *arg);
int					edit_export(t_env **my_env, char *key);
int					ft_unsetenv(t_env **my_env, char *key);
int					ft_unset(t_env **my_env, char *key);
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

void				builtin_env(t_env **my_env);
void				builtin_set(t_env **my_env);

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

int					dest_output(t_env **my_env);
int					dest_error_output(t_env **my_env);
void				close_file(t_env **my_env);
void				close_error_file(t_env **my_env);

/*
** execute_command.c
*/

int					exec_fork(char **command, t_env **my_env, char **env);
int					exec_command(t_arg *lst_arg, t_env **my_env);

#	endif
