/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_cd_canonical_b.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 18:35:07 by apruvost          #+#    #+#             */
/*   Updated: 2019/05/08 03:28:39 by apruvost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int		cd_canonical_testprev(t_cd *cd, size_t *a)
{
	int			i;
	struct stat	sb;

	if (cd->curpath[*a] == '.' && cd->curpath[*a + 1] == '.'
							&& cd->curpath[*a + 2] == '/')
		return (1);
	i = *a;
	while (cd->curpath[i] != '\0' && cd->curpath[i] != '/')
		i++;
	if (cd->curpath[i] == '/')
		cd->curpath[i] = '\0';
	if (stat(cd->curpath, &sb) == -1)
	{
		dprintf(2, "21sh: cd: Permission denied\n");
		cd->curpath[i] = '/';
		return (0);
	}
	cd->curpath[i] = '/';
	if ((sb.st_mode & S_IFMT) != S_IFDIR)
		return (0);
	return (1);
}

size_t	cd_canonical_getprevv(t_cd *cd, size_t i)
{
	while (i > 0)
	{
		i--;
		while (i > 0 && cd->curpath[i] == '/')
			i--;
		while (i > 0 && cd->curpath[i] != '/')
			i--;
		if (i == 0)
			return (1);
		else
			return (++i);
	}
	return (1);
}

int		cd_canonical_getprev(t_cd *cd, size_t *a, size_t *b)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 2;
	while (cd->curpath[i] != '\0')
	{
		if (cd->curpath[i] == '.' && cd->curpath[i + 1] == '.')
		{
			if (cd->curpath[i + j] == '/' || cd->curpath[i + j] == '\0')
			{
				while (cd->curpath[i + j] == '/')
					j++;
				*b = i + j;
				*a = cd_canonical_getprevv(cd, i);
				return (1);
			}
		}
		while (cd->curpath[i] != '\0' && cd->curpath[i] != '/')
			i++;
		if (cd->curpath[i] != '\0')
			i++;
	}
	return (0);
}

/*
** b. For each '..', if there is a preceding component and it is neither root nor '..', then :
**     i. If preceding component does not refer directory (ex. symbolic link), display error message and stop
**     ii. Preceding component, '/', '..' and '/' (if any) shall be deleted
*/

int		cd_canonical_b(t_cd *cd)
{
	size_t	a;
	size_t	b;
	size_t	len;

	a = 0;
	b = 0;
	while (cd_canonical_getprev(cd, &a, &b))
	{
		if (!cd_canonical_testprev(cd, &a))
		{
			dprintf(2, "21sh: cd: Component before \"..\" is not a directory\n");
			return (1);
		}
		len = ft_strlen(cd->curpath);
		len -= b - a;
		if (!cd_canonical_del(cd, a, b, len))
		{
			dprintf(2,"21sh: cd: error malloc\n");
			return (1);
		}
	}
	return (0);
}
