/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub_tab_fix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 13:06:57 by sbelondr          #+#    #+#             */
/*   Updated: 2019/04/08 11:06:52 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minilib.h"

void	ft_strsub_tab_fix(char (*lst)[BUF_S], char src[BUF_S], int start,
		int len)
{
	int	i;

	ft_bzero(*lst, BUF_S);
	i = -1;
	while (src[start] && ++i < len)
		(*lst)[i] = src[start + i];
}
