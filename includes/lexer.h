#ifndef LEXER_H
# define LEXER_H
#include "../libft/includes/libft.h"

typedef struct s_lex		t_lex;
typedef struct s_token		t_token;
typedef enum e_token_type	t_type;
typedef	struct s_tab_type	t_tab_type;

enum	e_token_type
{
	LPAR,
	RPAR,
	LBRACKET,
	RBRACKET,
	LBRACE,
	RBRACE,
	AMPERSAND,
	DAMPERSAND,
	SPIPE,
	DPIPE,
	SCOLON,
	DSCOLON,
	LESS,
	DLESS,
	LESSAMP,
	DLESSHYPH,
	GREAT,
	DGREAT,
	GREATPIPE,
	GREATAMP,
	LESSGREAT,
	SQUOTE,
	DQUOTE,
	TQUOTE,
	TILDE,
	DOLLARS,
	ASTERIX,
	HASHTAG,
	SLASH,
	BACKSLASH,
	NEWLINE,
	TAB,
	SPACE,
	NUMBER,
	WORD,
	CMD,
	DELIM,
	NUL,
};

struct s_token
{
	char	*data;
	t_type	type;
};

struct	s_lex
{
	t_token	*token;
	t_lex	*next;
	t_lex	*prev;
};

struct s_tab_type
{
	char	*str;
	t_type	type;
};

/* Array of function pointer */
void	set_tab_types(t_tab_type **tab_of_types);
void	compare_types(t_tab_type **tab_of_types, t_token **token, char *word);

/* Lexing */
t_lex	*lexer(char *input);
void	reading_input(char *input, t_lex **lex);
t_token	*check_type(t_tab_type **tab_of_types, char *input, int start, int end);
int		ft_isnumbers(char *str);

/* Creating token */
t_token	*create_token(char *str, t_type types);
t_token	*word_or_number(char *data);
t_lex	*add_delim(t_lex **lex);

/* DLL functions */

/* Creation */
t_lex	*new_node(t_token **tok);

/* Insertion */
void	dllinsfront(t_lex **head, t_lex **node);
void	dllinsback(t_lex **tail, t_lex **node);
void	dllinsafter(t_lex **prev_node, t_lex **node);
void	dllinsbefore(t_lex **next_node, t_lex **node);

/* Iteration */
void	dllprinthead(t_lex **head);
void	dllprinttail(t_lex **tail);
int		dlliter(t_lex **head);

/* Deletion */
t_lex	*dlldelfirst(t_lex **head);
t_lex	*dlldellast(t_lex **tail);
t_lex	*dlldelone(t_lex **head, char *data);
void	del_node(t_lex **node);

#endif
