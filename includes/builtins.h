#ifndef BUILTINS_H
# define BUILTINS_H

#include "env.h"

typedef struct		s_cd
{
	int		arg__;
	char	*directory;
	char	*curpath;
}					t_cd;

int		bt_exit(char **av);
int		bt_echo(char **av);

int		bt_cd(char **av);
int		cd_testcdpath(char *path, char *directory, char **test);
int		cd_testpath(char *path, char *directory, char **test);
int		cd_getnextpath(char *path);
int		cd_canonical(t_cd *cd);
int		cd_canonical_del(t_cd *cd, size_t a, size_t b, size_t len);
int		cd_canonical_a(t_cd *cd);
int		cd_canonical_getdot(t_cd *cd, size_t *a, size_t *b);
int		cd_canonical_b(t_cd *cd);
int		cd_canonical_getprev(t_cd *cd, size_t *a, size_t *b);
size_t	cd_canonical_getprevv(t_cd *cd, size_t i);
int		cd_canonical_testprev(t_cd *cd, size_t *a);
int		cd_canonical_c(t_cd *cd);
int		cd_canonical_getslash(t_cd *cd, size_t *a, size_t *b);
int		cd_chdir(t_cd *cd);
int		cd_err(t_cd *cd);

#endif
