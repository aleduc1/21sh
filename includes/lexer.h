/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 17:15:13 by aleduc            #+#    #+#             */
/*   Updated: 2019/05/06 22:35:26 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "libft.h"

typedef struct s_lex		t_lex;
typedef struct s_token		t_token;
typedef enum e_token_type	t_type;
typedef	struct s_tab_type	t_tab_type;
typedef	struct s_redir		t_redir;

enum	e_token_type
{
//	LPAR,
//	RPAR,
//	LBRACKET,
//	RBRACKET,
//	LBRACE,
//	RBRACE,
//	AMPERSAND,
//	DAMPERSAND,
	SPIPE,
//	DPIPE,
	SCOLON,
//	DSCOLON,
	LESS,
	DLESS,
	LESSAMP,
//	DLESSHYPH,
	GREAT,
	DGREAT,
	GREATPIPE,
	GREATAMP,
	LESSGREAT,
	SQUOTE,
	DQUOTE,
//	TQUOTE,
	TILDE,
	DOLLARS,
//	ASTERIX,
//	HASHTAG,
//	SLASH,
//	BACKSLASH,
//	NEWLINE,
//	TAB,
	SPACE,
	AMPGREAT,
	AMPLESS,
//	AMPGREATHYPH,
//	AMPLESSHYPH,
	LESSAMPHYPH,
	GREATAMPHYPH,
	NUMBER,
	WORD,
	CMD,
	DELIM,
	REDIR,
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
	t_redir	*redir;
	t_lex	*next;
	t_lex	*prev;
};

struct s_tab_type
{
	char	*str;
	t_type	type;
};

struct	s_redir
{
	char	**src_fd;
	char	*dest_fd;
	t_type	type;
	char	*filename;
	char	*heredoc;
	int		close;
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
t_lex	*detaching(t_lex **start, t_lex **end);
void	attach_redir_node(t_redir **redir_info, t_lex **before_start);

/* Implementing Redirect struct */
int		handle_redir(t_lex **lex);
int		cycle_redirect(t_lex **command_node);
int		handle_needed_redir(t_lex **command_node, t_lex **redir_node);
void	ft_default(t_redir **redir_info);

int		handle_great(t_lex **command_node);
int		handle_great_and(t_lex **command_node);
int		handle_and_great(t_lex **command_node);
int		handle_append(t_lex **command_node);
int		handle_less(t_lex **command_node);
int		handle_and_less(t_lex **command_node);
int		handle_less_and(t_lex **command_node);
int		handle_heredoc(t_lex **command_node);
int		handle_great_hyph(t_lex **command_node);
int		handle_less_hyph(t_lex **command_node);

/* Struct filling */
t_redir	*redir_struct_great(t_lex **start);
t_redir	*redir_struct_great_and(t_lex **start);
t_redir	*redir_struct_and_great(t_lex **start);
t_redir	*redir_struct_append(t_lex **start);
t_redir	*redir_struct_less(t_lex **start);
t_redir	*redir_struct_less_and(t_lex **start);
t_redir	*redir_struct_and_less(t_lex **start);
t_redir	*redir_struct_heredoc(t_lex **start);
t_redir	*redir_struct_great_hyph(t_lex **start);
t_redir	*redir_struct_less_hyph(t_lex **start);

/* Grammatical rules */
void	start_grammar_great(t_lex **start);
int		end_grammar_great(t_lex **start, t_lex **end, t_type type_check);
int		is_a_redirect(t_type type);

/* Removing Useless Space from the dll */
void	remove_space_token(t_lex **lexer);
void	remove_node(t_lex **node_cmd_space);
int		is_only_space(t_lex **node_cmd);

/* DLL functions */
/* Creation */
t_lex	*new_node(t_token **tok);
t_lex	*new_redir_node(t_token **tok, t_redir **redir_info);

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


/* Error */
void	ft_error(int code_error);

/* Cleaning */
void	clean_lex(t_lex **lex);
void	clean_inside_token(t_token **token);
void	clean_redir(t_redir **redir);

#endif
