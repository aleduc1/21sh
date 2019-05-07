/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_cd_utilstwo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 18:27:24 by apruvost          #+#    #+#             */
/*   Updated: 2019/05/07 16:29:05 by apruvost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int		cd_chdir(t_cd *cd, char ***env)
{
	char	*tmp;
	char	path[PATH_MAX];

	if (chdir(cd->curpath) == -1)
	{
		dprintf(2, "21sh: cd: permission denied: %s\n", cd->directory);
		return (1);
	}
	if (cd->arg_P)
	{
		tmp = ft_getenvval("PWD", *env);
		ft_setenv("PWD", getcwd(path, PATH_MAX), 1, env);
		ft_setenv("OLDPWD", tmp, 1, env);
	}
	else
	{
		tmp = ft_getenvval("PWD", *env);
		ft_setenv("PWD", cd->curpath, 1, env);
		ft_setenv("OLDPWD", tmp, 1, env);
	}
	return (0);
}

/*
** 9 - If curpath longer than {PATH_MAX} (including ter null) and directory not longer than {PATH_MAX} (including ter null) :
**     curpath shall be converted from absolute pathname to equ relative pathname if possible
**         This conversion always considered possible if PWD, with trailing '/' is an initial substring of curpath
**         Whether or not considered possile under other circumstances unspecified
**     Implementations may also apply this conversio if curpath not longer than {PATH_MAX} or directory was longer than {PATH_MAX}


int		cd_path_max(t_cd *cd, t_env *env)
{
	
}

*/

int		cd_canonical_del(t_cd *cd, size_t a, size_t b, size_t len)
{
	char	*tmp;
	size_t	i;
	size_t	j;

	if ((tmp = (char *)malloc(sizeof(char) * (len + 1))) == NULL)
		return (0);
	tmp[len] = '\0';
	i = 0;
	j = 0;
	while (cd->curpath[i] != '\0')
	{
		if (i == a && a != b)
			i = b;
		tmp[j] = cd->curpath[i];
		i++;
		j++;
	}
	ft_strdel(&(cd->curpath));
	cd->curpath = tmp;
	return (1);
}

/*
** 8 - curpath shall be converted to canonical form as follows :
**         a. dot components and any '/' that separate them from the next component shall be deleted
**         b. For each '..', if there is a preceding component and it is neither root nor '..', then :
**             i. If preceding component does not refer directory (ex. symbolic link), display error message and stop
**             ii. Preceding component, '/', '..' and '/' (if any) shall be deleted
**         c. An implementation ma further simplify curpath b removing any trailng '/' that are not also leading '/',
**            replacing multiple consecutive '/' by a single '/', and replacing three or more leading '/' by a single '/'
**     If after step 8, curpath is null, stop
*/

int		cd_canonical(t_cd *cd)
{
	if (cd_canonical_a(cd))
		return (0);
	ft_printf("Path before canonical b : %s\n", cd->curpath);
	if (cd_canonical_b(cd))
		return (0);
	ft_printf("Path after canonical b : %s\n", cd->curpath);
	cd_canonical_c(cd);
	if (cd->curpath[0] == '\0')
	{
		dprintf(2, "21sh: cd: path after canonicalization is null\n");
		return (0);
	}
	return (1);
}
