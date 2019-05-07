/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 17:56:32 by apruvost          #+#    #+#             */
/*   Updated: 2019/05/07 16:29:11 by apruvost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

/*
** cd [-L|-P] [directory]
** cd -
**
** cd utility steps (*curpath* is an intermediate value) :
**
** 1 - If no directory is given and HOME env empty or unset : implementation defined behavior and stop
**
** 2 - If no directory is given and HOME env set to no empty : directory is HOME env value
**
** 3 - If directory starts with '/' : set *curpath* to directory and go step 7
**
** 4 - If first component of directory is '.' or '..' : go step 6
**
** 5 - If ':' separated pathname of CDPATH set : test with each "pathname/directory"
**     If no pathname : test "./directory"
**     If result points to directory : set curpath to that string and go step 7
**
** 6 - Set curpath to directory
**
** 7 - If -P option : go step 10
**     If curpath does not begin with '/' : set curpath to "PWD/curpath"
**
** 8 - curpath shall be converted to canonical form as follows :
**         a. dot components and any '/' that separate them from the next component shall be deleted
**         b. For each '..', if there is a preceding component and it is neither root nor '..', then :
**             i. If preceding component does not refer directory (ex. symbolic link), display error message and stop
**             ii. Preceding component, '/', '..' and '/' (if any) shall be deleted
**         c. An implementation ma further simplify curpath b removing any trailng '/' that are not also leading '/',
**            replacing multiple consecutive '/' by a single '/', and replacing three or more leading '/' by a single '/'
**            If after step 8, curpath is null, stop
**
** 9 - If curpath longer than {PATH_MAX} (including ter null) and directory not longer than {PATH_MAX} (including ter null) :
**     curpath shall be converted from absolute pathname to equ relative pathname if possible
**         This conversion always considered possible if PWD, with trailing '/' is an initial substring of 
**         Whether or not considered possile under other circumstances unspecified
**     Implementations may also apply this conversio if curpath not longer than {PATH_MAX} or directory was longer than {PATH_MAX}
**
** 10 - cd shall use equ to chdir() function with curpath as path argument
**      If these action fail for any reason, display error and stop
**      If not -P option : PWD env var set to curpath before step 9
**      If -P option : PWD env var set to string that would be output by pwd -P
*       If insufficient permission o new directory, or any parent directory, to determine current working directory, value PWD unspecified
**
** If, during above steps, PWD variable is set, change OLD_PWD to value of old working directory (current working directory prior to cd call) 
*/

static int	cd_stepten(t_cd *cd, char ***env)					// Step 10
{
	struct stat	sb;
	
	ft_printf("Test accès %s\n", cd->curpath);
	if (stat(cd->curpath, &sb) == -1)
	{
		dprintf(2, "21sh: cd: permission denied\n");
		return (1);
	}
	if ((sb.st_mode & S_IFMT) != S_IFDIR)
	{
		dprintf(2, "21sh: cd: no such file or directory: %s\n", cd->directory);
		return (1);
	}
	if (cd_chdir(cd, env))
		return (1);
	return (0);
}

static int	cd_stepsev(t_cd *cd, char ***env)
{
	char	*bin;

	if (cd->arg_P == 1)											// Step 7
		return (cd_stepten(cd, env));
	if (cd->curpath[0] != '/')
	{
		bin = ft_getenvval("PWD", *env);
		cd->curpath = ft_jointhree(bin, "/", cd->curpath);
		ft_strdel(&bin);
	}
	if (!cd_canonical(cd))											// Step 8
		return (1);
//	cd_path_max(cd, env);										// Step 9
	return (cd_stepten(cd, env));
}

static int	cd_stepfive(t_cd *cd, char **env)
{
	char	*test;
	char	*path;
	int		j;

	test = NULL;
	if (ft_isenvempty("CDPATH", env))
	{
		if (!cd_testpath(".", cd->directory, &test))
			return (0);
		cd->curpath = test;
		return (1);
	}
	path = ft_getenvval("CDPATH", env);
	j = 7;
	while (path[j] != '\0')
	{
		if ((cd_testcdpath(&(path[j]), cd->directory, &test)))
		{
			cd->curpath = test;
			ft_strdel(&path);
			return (1);
		}
		j += getnextpath(&(path[j]));
	}
	ft_strdel(&path);
	return (0);
}

static void	cd_init(char **av, t_cd *cd)
{
	int		i;

	cd->arg_P = 0;
	cd->arg_L = 0;
	i = cd_getargs(av, cd);										// V
	cd->directory = av[i];
}

int			ft_cd(char **av, char ***env)
{
	t_cd	cd;

	cd_init(av, &cd);							// V
	if (cd.directory == NULL && ft_isenvempty("HOME", *env))	// Step 1
		return (1);
	if (cd.directory == NULL)									// Step 2
		cd.directory = ft_getenvval("HOME", *env);
	if (cd.directory[0] == '/')									// Step 3
	{
		cd.curpath = ft_strdup(cd.directory);
		return (cd_stepsev(&cd, env));
	}
	if (cd.directory[0] != '.' ||
		(cd.directory[0] != '.' && cd.directory[1] != '.'))		// Step 4
	{
		if (cd_stepfive(&cd, *env))								// Step 5
			return (cd_stepsev(&cd, env));
		dprintf(2, "21sh: cd: %s: No such file or directory\n", cd.directory);
		return (1);
	}
	cd.curpath = ft_strdup(cd.directory);						// Step 6
	return (cd_stepsev(&cd, env));
}
