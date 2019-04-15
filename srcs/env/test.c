/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 10:35:53 by sbelondr          #+#    #+#             */
/*   Updated: 2019/04/15 11:11:04 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int		main(void)
{
	int	in;
	int	result;
	int fd;
	
	in = dup(STDOUT_FILENO);
	fd = open("log", O_RDWR);
	result = dup2(fd, in);
//	close(in);
	printf("coucou result = %d\n", fd);
	result = dup2(in, STDOUT_FILENO);
	printf("result %d, in = %d\n", result, in);
	close(fd);
	return (0);
}
