/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 10:40:08 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/22 10:23:12 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job.h"
#include "sh21.h"

/*
** tcgetattr(shell->term, &(shell->term_shell));
*/

static t_shell	*init_shell_list(void *term)
{
	t_shell			*shell;
	struct termios	*t;

	if (!(shell = (t_shell*)malloc(sizeof(t_shell) * 1)))
		return (NULL);
	shell->pgid = getpgrp();
	shell->term = STDIN_FILENO;
	shell->interactive = isatty(shell->term);
	t = (struct termios*)term;
	shell->term_shell = *t;
	return (shell);
}

t_shell			**static_shell(void *term)
{
	static t_shell	*shell;

	if (!shell)
		shell = init_shell_list(term);
	return (&shell);
}

t_shell			*get_shell(void)
{
	t_shell **shell;

	shell = static_shell(NULL);
	return (*shell);
}

void			delete_shell(void)
{
	t_shell	**shell;

	shell = static_shell(NULL);
	free(*shell);
	*shell = NULL;
}
