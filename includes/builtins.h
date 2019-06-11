/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 16:01:05 by sbelondr          #+#    #+#             */
/*   Updated: 2019/06/11 17:10:48 by apruvost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef BUILTINS_H
#	define BUILTINS_H

#include "sh21.h"
#include "env.h"
#include <sys/param.h>

typedef struct		s_cd
{
	int		arg__;
	int		arg_L;
	int		arg_P;
	char	*directory;
	char	*curpath;
}					t_cd;

typedef struct		s_alias
{
	char	*key;
	char	*value;
}					t_alias;

typedef struct		s_ht_alias
{
	int		size;
	int		base_size;
	int		count;
	t_alias	**alias;
}					t_ht_alias;

# define HT_ALIAS_HASH_ONE 3
# define HT_ALIAS_HASH_TWO 7
# define HT_ALIAS_BASE_SIZE 50


int					bt_exit(char **av);
int					bt_echo(char **av, t_redirection *r);


int					bt_cd(char **av);
int					cd_testcdpath(char *path, char *directory, char **test);
int					cd_testpath(char *path, char *directory, char **test);
int					cd_getnextpath(char *path);
int					cd_canonical(t_cd *cd);
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

int					bt_alias(char **av);
int					bt_unalias(char **av);

void				alias_del(t_alias *alias);
t_alias				*alias_new_item(const char *k, const char *v);
t_ht_alias			*ht_alias_new(void);
t_ht_alias			*ht_alias_new_sized(const int base_size);
void				ht_alias_del(t_ht_alias *ht);
int					ht_alias_get_hash(const char *s, const int num, const int attempt);
int					ht_alias_hash(const char *s, const int a, const int m);
void				ht_alias_insert(t_ht_alias *ht, const char *key, char *val);
char				*ht_alias_search(t_ht_alias *ht, const char *key);
void				ht_alias_delete(t_ht_alias *ht, const char *key);
void				ht_alias_resize(t_ht_alias *ht, const int base_size);
void				ht_alias_copy(t_ht_alias *ht, t_ht_alias *new_ht);
void				ht_alias_resize_down(t_ht_alias *ht);
void				ht_alias_resize_up(t_ht_alias *ht);
void				ht_alias_table_null(t_alias **alias, int size);

#	endif
