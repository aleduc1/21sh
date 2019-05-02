#ifndef LEXER_H
# define LEXER_H
# include "libft.h"

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
	AMPGREAT,
	AMPLESS,
	AMPGREATHYPH,
	AMPLESSHYPH,
	LESSAMPHYPH,
	GREATAMPHYPH,
	NUMBER,
	WORD,
	CMD,
	DELIM,
	NUL,
};

struct s_token
{
	char	*data;
	t_lex	*command;
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
int		handle_whitespace(char *input, int i, t_lex **lex);
int		ft_isnumbers(char *str);


/* Creating token */
t_token	*create_token(char *str, t_type types);
t_token	*create_command_token(t_lex **command, t_type types);
t_token	*word_or_number(char *data);
t_lex	*add_delim(t_lex **lex);


/* Parsing */
/* Implementing SimpleCommandToken */
void	simple_command(t_lex **head);

/* Delim */
void	set_delim(t_lex **head, t_lex **start, t_lex **end);
t_lex	*identify_delim(t_lex **start, t_lex **end);

/* TypeCheck */
int		type_to_ignore(t_type type);
int		type_to_end_on(t_type type);

/* Attach */
void	detach(t_lex **start, t_lex **end);
void	attach(t_lex **head, t_lex **node, t_lex **end);


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
t_lex	*dlllastnode(t_lex **head);
int		dlliter(t_lex **head);

/* Deletion */
t_lex	*dlldelfirst(t_lex **head);
t_lex	*dlldellast(t_lex **tail);
t_lex	*dlldelone(t_lex **head, char *data);
void	dll_del_node(t_lex **node);


/*
** Cleaning
*/

void	clean_lex(t_lex **lex);

#endif
