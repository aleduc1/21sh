#include "sh21.h"
#include "lexer.h"

int		main(int ac, char **av, char **environ)
{
	char	*line;
	t_lex	*lex;

	line = NULL;
	lex = NULL;
	while (42)
	{
		if (!lex)
		{
			if (ac && av && environ)
			{
				ft_putstr("~> ");
				if (get_next_line(STDIN_FILENO, &line))
				{
					if (line[0])
						lex = lexer(line);
					ft_putendl(line);
				}
				if (line)
					free(line);
			}
		}
	}
	return (0);
}
