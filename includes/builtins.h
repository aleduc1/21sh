/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 16:01:05 by sbelondr          #+#    #+#             */
<<<<<<< HEAD
<<<<<<< HEAD
/*   Updated: 2019/06/02 17:36:03 by sbelondr         ###   ########.fr       */
=======
/*   Updated: 2019/05/31 08:47:03 by apruvost         ###   ########.fr       */
>>>>>>> First push alias branch
=======
/*   Updated: 2019/06/07 16:09:26 by apruvost         ###   ########.fr       */
>>>>>>> started implementing hashtable alias
/*                                                                            */
/* ************************************************************************** */

#	ifndef BUILTINS_H
#	define BUILTINS_H

#include "env.h"
#include <sys/param.h>

<<<<<<< HEAD
=======
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

<<<<<<< HEAD
>>>>>>> First push alias branch
=======
typedef struct		s_ht_alias
{
	int		size;
	int		count;
	t_alias	**alias;
}					t_ht_alias;


>>>>>>> started implementing hashtable alias
int					bt_exit(char **av);
int					bt_echo(char **av, t_redirection *r);

#	endif
