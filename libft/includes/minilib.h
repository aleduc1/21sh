/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilib.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 19:42:20 by sbelondr          #+#    #+#             */
/*   Updated: 2019/04/08 11:07:29 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef MINILIB_H
#	define MINILIB_H

#include <unistd.h>
#include <strings.h>
#include <stdlib.h>

#include "libft.h"

#define BUF_S		1024
#define BUF_SIZE	30

#include "libft.h"
#include "ft_printf.h"
/*
typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;
*/
char				**ft_strsplit(char const *s, char c);
int					get_end_line(char *file);
int					ft_numlen(int n);
int					ft_chr_index(char *s, char c);
int					ft_strchr_exist(char *s, char c);
int					ft_chrn_index(char *s, char c, int i);
void				ft_deplace(char (*lst)[BUF_S]);
void				ft_pow_array_fix(int i, char (*nb)[BUF_S]);
void				ft_reverse_tablo(char (*lst)[BUF_S]);
void				ft_strsub_tab_fix(char (*lst)[BUF_S], char src[BUF_S],
		int start, int len);

void				ft_arraydel(char ***line);
char				**ft_arraydup(char **line);
void				ft_arraydelline(char ***src, int line);
int					ft_arraylen(char **src);
void				ft_arraydisplay(char **src);
char				**ft_arraysub(char **src, int start, int len);
char				**ft_arrayjoin(char **src, char *str);

#	endif
