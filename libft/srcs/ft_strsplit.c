/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 09:07:14 by skuppers          #+#    #+#             */
/*   Updated: 2018/10/12 16:27:36 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		**countwords(char const *s, char c, size_t len)
{
	unsigned int	i;
	unsigned int	nbword;
	char			**words;

	i = 0;
	nbword = 0;
	while (i < len && s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			while (s[i] != c && s[i] != '\0')
				i++;
			nbword++;
		}
	}
	if (!(words = (char**)malloc(sizeof(*words) * (nbword + 2))))
		return (NULL);
	return (words);
}

static size_t	wordlength(char const *s, char c, size_t len, unsigned int i)
{
	size_t wlen;

	wlen = 0;
	while (s[i] != c && s[i] && i++ < len)
		wlen++;
	return (wlen);
}

char			**ft_strsplit(char const *s, char c)
{
	size_t			len;
	unsigned int	i;
	char			**words;
	unsigned int	index;

	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	words = countwords(s, c, len);
	if (!words)
		return (NULL);
	i = 0;
	index = 0;
	while (i < len && s[i])
	{
		if (s[i] == c)
		{
			i++;
			continue;
		}
		words[index++] = ft_strsub(s, i, wordlength(s, c, len, i));
		i += wordlength(s, c, len, i);
	}
	words[index] = 0;
	return (words);
}
