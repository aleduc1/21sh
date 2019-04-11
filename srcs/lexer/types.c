/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 17:21:37 by aleduc            #+#    #+#             */
/*   Updated: 2019/04/02 19:18:48 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	set_tab_types(t_tab_type **tab_of_types)
{
	(*tab_of_types) = (t_tab_type *)ft_memalloc(sizeof(t_tab_type) * 34);
	(*tab_of_types)[0].str = "(";
	(*tab_of_types)[0].type = LPAR;
	(*tab_of_types)[1].str = ")";
	(*tab_of_types)[1].type = RPAR;
	(*tab_of_types)[2].str = "[";
	(*tab_of_types)[2].type = LBRACKET;
	(*tab_of_types)[3].str = "]";
	(*tab_of_types)[3].type = RBRACKET;
	(*tab_of_types)[4].str = "{";
	(*tab_of_types)[4].type = LBRACE;
	(*tab_of_types)[5].str = "}";
	(*tab_of_types)[5].type = RBRACE;
	(*tab_of_types)[6].str = "&";
	(*tab_of_types)[6].type = AMPERSAND;
	(*tab_of_types)[7].str = "&&";
	(*tab_of_types)[7].type = DAMPERSAND;
	(*tab_of_types)[8].str = "|";
	(*tab_of_types)[8].type = SPIPE;
	(*tab_of_types)[9].str = "||";
	(*tab_of_types)[9].type = DPIPE;
	(*tab_of_types)[10].str = ";";
	(*tab_of_types)[10].type = SCOLON;
	(*tab_of_types)[11].str = ";;";
	(*tab_of_types)[11].type = DSCOLON;
	(*tab_of_types)[12].str = "<";
	(*tab_of_types)[12].type = LESS;
	(*tab_of_types)[13].str = "<<";
	(*tab_of_types)[13].type = DLESS;
	(*tab_of_types)[14].str = "<&";
	(*tab_of_types)[14].type = LESSAMP;
	(*tab_of_types)[15].str = "<<-";
	(*tab_of_types)[15].type = DLESSHYPH;
	(*tab_of_types)[16].str = ">";
	(*tab_of_types)[16].type = GREAT;
	(*tab_of_types)[17].str = ">>";
	(*tab_of_types)[17].type = DGREAT;
	(*tab_of_types)[18].str = ">|";
	(*tab_of_types)[18].type = GREATPIPE;
	(*tab_of_types)[19].str = ">&";
	(*tab_of_types)[19].type = GREATAMP;
	(*tab_of_types)[20].str = "<>";
	(*tab_of_types)[20].type = LESSGREAT;
	(*tab_of_types)[21].str = "'";
	(*tab_of_types)[21].type = SQUOTE;
	(*tab_of_types)[22].str = "\"";
	(*tab_of_types)[22].type = DQUOTE;
	(*tab_of_types)[23].str = "`";
	(*tab_of_types)[23].type = TQUOTE;
	(*tab_of_types)[24].str = "~";
	(*tab_of_types)[24].type = TILDE;
	(*tab_of_types)[25].str = "$";
	(*tab_of_types)[25].type = DOLLARS;
	(*tab_of_types)[26].str = "*";
	(*tab_of_types)[26].type = ASTERIX;
	(*tab_of_types)[27].str = "#";
	(*tab_of_types)[27].type = HASHTAG;
	(*tab_of_types)[28].str = "/";
	(*tab_of_types)[28].type = SLASH;
	(*tab_of_types)[29].str = "\\";
	(*tab_of_types)[29].type = BACKSLASH;
	(*tab_of_types)[30].str = "\n";
	(*tab_of_types)[30].type = NEWLINE;
	(*tab_of_types)[31].str = "\t";
	(*tab_of_types)[31].type = TAB;
	(*tab_of_types)[32].str = " ";
	(*tab_of_types)[32].type = SPACE;
	(*tab_of_types)[33].str = NULL;
	(*tab_of_types)[33].type = NUL;
}
