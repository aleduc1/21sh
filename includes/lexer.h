#ifndef LEXER_H
# define LEXER_H
# include "libft.h"

typedef struct s_lex		t_lex;
typedef struct s_token		t_token;
typedef enum e_token_type	t_type;
typedef	struct s_ptrf		t_ptrf;

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
	DELIM,
};

struct s_token
{
	char	*data;
	char	**cmd;
	t_type	type;
};

struct	s_lex
{
	t_token	*token;
	t_lex	*next;
	t_lex	*prev;
};

struct s_ptrf
{
	char	*str;
	t_token	*(*f)(void);
};

/* Array of function pointer */
void	set_tab_types(t_ptrf **fptr);
void	compare_types(t_ptrf **fptr, t_token **token, char *word);

/* Lexing */
t_lex	*lexer(char *input);
void	reading_input(char *input, t_lex **lex);
t_token	*check_type(t_ptrf **fptr, char *input, int start, int end);
int		ft_isnumbers(char *str);

/* Creating token */
t_token	*lpar(void);
t_token	*rpar(void);
t_token	*lbracket(void);
t_token	*rbracket(void);
t_token	*lbrace(void);
t_token	*rbrace(void);
t_token	*ampersand(void);
t_token	*dampersand(void);
t_token	*spipe(void);
t_token	*dpipe(void);
t_token	*scolon(void);
t_token	*dscolon(void);
t_token	*less(void);
t_token	*dless(void);
t_token	*lessamp(void);
t_token	*dlesshyph(void);
t_token	*great(void);
t_token	*dgreat(void);
t_token	*greatpipe(void);
t_token	*greatamp(void);
t_token	*lessgreat(void);
t_token	*squote(void);
t_token	*dquote(void);
t_token	*tquote(void);
t_token	*tilde(void);
t_token	*dollars(void);
t_token	*asterix(void);
t_token	*hashtag(void);
t_token	*slash(void);
t_token	*backslash(void);
t_token	*space(void);
t_token	*tab_key(void);
t_token	*new_line(void);
t_token	*delim(void);
t_token	*number(char *numbers);
t_token	*word(char *words);
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
