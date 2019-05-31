/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 16:01:05 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/31 19:39:43 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef BUILTINS_H
#	define BUILTINS_H

#include "env.h"
#include <sys/param.h>
/*
typedef struct		s_cd
{
	int		arg__;
	int		arg_L;
	int		arg_P;
	char	*directory;
	char	*curpath;
}					t_cd;
*/
int					bt_exit(char **av);
int					bt_echo(char **av, t_redirection *r);


//int					bt_cd(char **av);
//int					cd_testcdpath(char *path, char *directory, char **test);
//int					cd_testpath(char *path, char *directory, char **test);
//int					cd_getnextpath(char *path);
/*int					cd_canonical(t_cd *cd);
int					cd_canonical_a(t_cd *cd);
int					cd_canonical_getdot(t_cd *cd, size_t *a, size_t *b);
int					cd_canonical_b(t_cd *cd);
int					cd_canonical_getprev(t_cd *cd, size_t *a, size_t *b);
size_t				cd_canonical_getprevv(t_cd *cd, size_t i);
int					cd_canonical_testprev(t_cd *cd, size_t *a);
int					cd_canonical_c(t_cd *cd);
int					cd_canonical_getslash(t_cd *cd, size_t *a, size_t *b);
int					cd_canonical_del(t_cd *cd, size_t a, size_t b, size_t len);
int					cd_chdir(t_cd *cd);
int					cd_err(t_cd *cd);
int					cd_getopt(char ac, char **av, t_cd *cd);

int					ft_getopt(int ac, char *const *av, const char *optstr);
void				ft_getopt_reset(void);
*/
#	endif
