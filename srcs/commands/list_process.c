/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 10:50:50 by sbelondr          #+#    #+#             */
/*   Updated: 2019/06/02 18:20:30 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

t_process	*init_process(void)
{
	t_process	*p;

	if (!(p = (t_process*)malloc(sizeof(t_process) * 1)))
		return (NULL);
	p->av = NULL;
	p->r = NULL;
	p->next = NULL;
	return (p);
}

void		delete_process(t_process **p)
{
	t_process	*next;

	while (*p)
	{
		next = ((*p)->next) ? (*p)->next : NULL;
		ft_arraydel(&((*p)->av));
		delete_redirection(&((*p)->r));
		free(*p);
		(*p) = NULL;
		(*p) = next;
	}
}

void		add_process_s(t_process *p, char **av, t_redirection *r)
{
	if (!p)
		return ;
	while (p->av)
	{
		if (!p->next)
			p->next = init_process();
		p = p->next;
	}
	if (p)
	{
		p->av = ft_arraydup(av);
		p->r = r;
	}
}
