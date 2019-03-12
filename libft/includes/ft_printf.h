/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 19:15:44 by aleduc            #+#    #+#             */
/*   Updated: 2018/11/20 13:15:40 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft.h"
# include <stdarg.h>

# define CHAR 'c'
# define STRING 's'
# define INT 'd'

# define BUFFER_SIZE 4096

typedef struct	s_printf
{
	int			padding;
	int			padding_v1;
	int			padding_v2;
	int			negative;
}				t_printf;

void			ft_printf_fd(int fd, const char *str, ...);
void			ft_printf_va(int fd, const char *str, va_list args);

int				add_char_to_buffer(char *buffer, int c, t_printf *pf);
int				add_string_to_buffer(char *buffer, char *string, t_printf *pf);
int				add_int_to_buffer(char *buffer, int i, t_printf *pf);
int				set_struct_negative(t_printf *pf);
int				set_struct_padding(t_printf *pf, int a, int b);
#endif
