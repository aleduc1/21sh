/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_end_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 10:48:31 by sbelondr          #+#    #+#             */
/*   Updated: 2019/04/08 10:02:12 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <fcntl.h>

int		get_end_line(char *file)
{
	int		fd;
	int		verif;
	char	*str;

	fd = open(file, O_RDWR);
	verif = 0;
	while (get_next_line(fd, &str) != -1)
		ft_strdel(&str);
	return (fd);
}
