/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 17:21:29 by aleduc            #+#    #+#             */
/*   Updated: 2019/03/18 16:23:00 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

t_token	*check_type(char *input, int start, int end)
{
	t_ptrf	*fptr;
	char	*word;
	t_token	*token;

	word = ft_strsub(input, start, end - start);
	ft_putstr("This is the word copied : ");
	ft_putendl(word);
	set_tab_types(&fptr);
	token = compare_types(fptr, word);	/* Si correspondant : function -> creer un token; sinon creer un token mot ou number */
	ft_memdel((void **)&word);
/* Free tout les pointeurs : token apres l'avoir return pour reading input
	** Et creer le tableau dans une fonction plus haute dans la stack pour pouvoir le free a la fin du lexing
	 */
	return (token);
}

int		skip_whitespace(char *str, int i) /* Mettre cette fonction dans la libft */
{
	int		cpy;

	cpy = i;
	while (str[cpy] && ft_isspace(str[cpy]))
		cpy++;
	return (cpy);
}

void	reading_input(char *input, t_lex **lex)
{
	int		i;
	int		j;
	int		to_check;
	t_token	*tok;

	tok = NULL;
	to_check = 0;
	i = 0;
	j = 0;
	while (input[i])
	{
		i = skip_whitespace(input, i);
		j = i;
		while (input[i] && ft_isalpha(input[i]))
		{
			i++;
			to_check = 1;
		}
		if (to_check)
		{
			tok = check_type(input, j, i);
			add_token(lex, tok);
			to_check = 0;
		}
	}
}

t_lex	*lexer(char *input)
{
	t_lex	*lex;

	lex = NULL;
	if (ft_strcmp(input, "exit") == 0)
		exit(0);
	reading_input(input, &lex);
	return (lex);
}
