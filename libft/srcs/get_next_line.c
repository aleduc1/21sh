/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 09:34:18 by sbelondr          #+#    #+#             */
/*   Updated: 2019/04/12 08:33:47 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_endline(char *str)
{
	int	i;

	i = -1;
	if (!str)
		return (-1);
	while (str[++i])
		if (str[i] == '\n')
			break ;
	return (i);
}

int		ft_read(const int fd, char **str)
{
	char	buf[BUF_S];
	char	*tmp;
	int		verif;

	ft_bzero(buf, BUF_S);
	while ((verif = read(fd, buf, (BUF_S - 1))) > 0)
	{
		buf[verif] = '\0';
		tmp = (*str) ? ft_strjoin((*str), buf) : ft_strdup(buf);
		ft_strdel(&(*str));
		(*str) = ft_strdup(tmp);
		ft_strdel(&tmp);
		if (ft_strchr_exist(*str, '\n'))
			break ;
	}
	if (verif == -1)
		ft_strdel(&(*str));
	return (verif);
}

int		ft_verif(int fd, char **str)
{
	if (fd < 0)
		return (-1);
	if (!(*str))
	{
		if (!((*str) = ft_strnew(BUF_S)))
			return (-1);
	}
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	static char	*str;
	char		*tmp;
	int			verif;

	if (ft_verif(fd, &str) == -1)
		return (-1);
	verif = ft_read(fd, &str);
	if (verif == -1)
	{
		ft_strdel(&str);
		return (-1);
	}
	verif = ft_endline(str);
	if (str[0])
	{
		(*line) = ft_strsub(str, 0, verif);
		tmp = ft_strsub(str, verif + 1, ft_strlen(str));
		ft_strdel(&str);
		str = ft_strdup(tmp);
		ft_strdel(&tmp);
		return (1);
	}
	else
	{
		ft_strdel(&str);
		return (-1);
	}
	ft_strdel(&str);
	return (0);
}
