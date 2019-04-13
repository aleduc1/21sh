#include "lexer.h"

/*
** Made a separate function to be able to use it for start and end
*/ 

int		IsOperator(t_type type)
{
	if (type == SPIPE || type == DPIPE || type == AMPERSAND || type == DAMPERSAND || type == SCOLON || type == DSCOLON)
		return (1);
	return (0);
}

/*
** We want to end on the node of one of those type
*/

int		TypeToEndOn(t_type type)
{
	if (IsOperator(type) || type == DELIM)
		return (0);
	return (1);
}

/*
** We want to start on the node after those type
*/

int		TypeToIgnore(t_type	type)
{
	if (IsOperator(type) || type == DELIM || type == CMD)
		return (1);
	return (0);
}
