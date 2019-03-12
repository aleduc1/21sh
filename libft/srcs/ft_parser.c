/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 19:19:22 by aleduc            #+#    #+#             */
/*   Updated: 2018/11/09 19:31:33 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		set_struct_negative(t_printf *pf)
{
	pf->negative = 1;
	return (1);
}

int		set_struct_padding(t_printf *pf, int arg0, int arg1)
{
	pf->padding = 1;
	pf->padding_v1 = arg0;
	pf->padding_v2 = arg1;
	return (3);
}

int		add_char_to_buffer(char *buffer, int c, t_printf *tpf)
{
	char	*tmp;
	char	*word;
	char	*align;

	tmp = ft_strnew(1);
	if (c < 32 || c > 126)
		c = 48;
	tmp[0] = c;
	if (tpf->padding == 1)
	{
		word = ft_strnew(tpf->padding_v2);
		word = ft_strncpy(word, tmp, 1);
		align = ft_strnew(tpf->padding_v1 - 1);
		ft_memset(align, ' ', tpf->padding_v1 - 1);
		if (tpf->negative)
			word = ft_strjoinfree(word, align, 3);
		else
			word = ft_strjoinfree(align, word, 3);
	}
	else
		word = ft_strdup(tmp);
	ft_strcat(buffer, word);
	ft_strdel(&word);
	ft_strdel(&tmp);
	return (1);
}

int		add_string_to_buffer(char *buffer, char *str, t_printf *tpf)
{
	char	*word;
	char	*align;
	char	*tmp;

	if (str == NULL)
		tmp = ft_strdup("(NULL)");
	else
		tmp = ft_strdup(str);
	if (tpf->padding == 1)
	{
		word = ft_strnew(tpf->padding_v2);
		word = ft_strncpy(word, tmp, tpf->padding_v2);
		align = ft_strnew(tpf->padding_v1 - tpf->padding_v2);
		ft_memset(align, ' ', tpf->padding_v1 - tpf->padding_v2);
		if (tpf->negative)
			word = ft_strjoinfree(word, align, 3);
		else
			word = ft_strjoinfree(align, word, 3);
	}
	else
		word = ft_strdup(tmp);
	ft_strcat(buffer, word);
	ft_strdel(&word);
	ft_strdel(&tmp);
	return (1);
}

int		add_int_to_buffer(char *buffer, int i, t_printf *tpf)
{
	char	*word;
	char	*align;
	char	*tmp;

	tmp = ft_itoa(i);
	if (tpf->padding == 1)
	{
		word = ft_strnew(tpf->padding_v2);
		word = ft_strncpy(word, tmp, tpf->padding_v2);
		align = ft_strnew(tpf->padding_v1 - tpf->padding_v2);
		ft_memset(align, ' ', tpf->padding_v1 - tpf->padding_v2);
		if (tpf->negative)
			word = ft_strjoinfree(word, align, 3);
		else
			word = ft_strjoinfree(align, word, 3);
	}
	else
		word = ft_strdup(tmp);
	ft_strcat(buffer, word);
	ft_strdel(&word);
	ft_strdel(&tmp);
	return (1);
}
