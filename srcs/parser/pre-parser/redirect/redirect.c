/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 11:00:04 by aleduc            #+#    #+#             */
/*   Updated: 2019/05/04 17:25:40 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdio.h>

void	ft_default(t_redir **redir_info)
{
	t_redir	*ptr;
	t_type	t;

	ptr = *redir_info;
	t = ptr->type;
	if (t == GREAT || t == LESSAMP || t == AMPLESS)
		ptr->src_fd[0] = ft_strdup("1");
	else if (t == GREATAMP || t == AMPGREAT)
	{
		ptr->src_fd[0] = ft_strdup("1");
		ptr->src_fd[1] = ft_strdup("2");
	}
	else if (t == LESS)
		ptr->src_fd[0] = ft_strdup("0");
}

/*
** Testing fct
*/

void	print_struct(t_redir **redir_info)
{
 	t_redir	*ptr;
 
 	ptr = *redir_info;
 	printf("src_fd : %s\ndest_fd : %s\n type : %d\nfilename : %s\nHeredoc : %s\nclose : %d\n", ptr->src_fd[0], ptr->dest_fd, ptr->type, ptr->filename, ptr->heredoc, ptr->close);
}

void	handle_redir(t_lex **lex)
{
	t_lex	*ptr;

	ptr = *lex;
	while (ptr)
	{
		if (ptr->token->type == CMD)
		{
			handle_great(&ptr);
			handle_great_and(&ptr);
			//		handle_and_upper(&ptr);
		}
		ptr = ptr->next;
	}
}
