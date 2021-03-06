#ifndef GRAMMAR_H
# define GRAMMAR_H
# include <stdio.h>
# include <libft/libft.h>
# include <libft/implemt.h>
# include <dlist.h>

/*
**	Grammar defines
**
**	Thanks a lot bash!
**
**	is_digit : {0, 1, ..., 9}
**	is_letter : {a, ..., z, A, ..., Z}
**	is_word : t_word*
**	is_number : {is_letter} | {number, is_letter}
**	is_wordlist : t_wordlist*
**	is_command : t_command*
**	is_redirection : t_redirection*
**	is_assig : {word} = {number} | {word} = {letter}
**	is_common_operator : {-, +}
**	is_logical_operator : {&&, ||}
*/
# define IS_DIGIT 1
# define IS_LETTER 2
# define IS_WORD 3
# define IS_NUMBER 4
# define IS_WORDLIST 5
# define IS_COMMAND 6
# define IS_REDIRECTION 7
# define IS_ASSIGNEMNT 8
# define IS_OPERATOR 9
# define GRAMMAR_N_TYPE 10

/*
**	========================================
**	========== WORD and WORD LIST ==========
**	========================================
**
**	-> Word flags
**
**	WORD_VOID			: a simple string
**	WORD_DOLLAR			: set if token is a dollard ($HOME, $*, ...)
**	WORD_QUOTE			: set if token is a quote/dquote/bquote
**	WORD_REGEX			: set if token is a REGEX expression
**	WORD_OPERATOR		: &&, ||, ... (a logical operator)
**	WORD_REDIRECTION	: <, <<, >, >>, ;, ... (a redirection operator)
**	WORD_OPARENTHESIS	: (	begin of a subshell
**	WORD_CPARENTHESIS	: ) end of a subshell
**	WORD_ASSIGNMENT		: = assigmnt expression
*/
# define WORD_VOID 0
# define WORD_DOLLAR 1
# define WORD_QUOTE 2
# define WORD_REGEX 3
# define WORD_OPERATOR 4
# define WORD_REDIRECTION 5
# define WORD_OPARENTHESIS 6
# define WORD_CPARENTHESIS 7
# define WORD_ASSIGNMENT 8

/*
**	-> Word data
**
**	token			: expression
**	len				: token's length
**	dollard			: there is a dollard ($HOME, $1, $#, ...)
**	asign			: is an assignemt
**	quote			: is a quote / dquote or bquote
*/
typedef struct			s_word
{
	char				*token;
	int					len;
	int					type;
	int					dollar;
	int					quote;
	int					asign;
}						t_word;

/*
**	-> Word linked-list
*/
typedef struct			s_wordlist
{
	struct s_wordlist	*next;
	t_word				*word;
}						t_wordlist;


/*
**	==================================
**	========== REDIRECTIONS ==========
**	==================================
**
**	-> Redirection flags
**
**		-> types
**	0 : <
**	1 : >
**	2 : <<
**	3 : >>
**	4 : |
**	5 : <&
**	6 : >&
**	7 : <-
**	8 : >-
**	9 : <<-
**	10 : >>-
**	11 : <>
**	12 : >|
**	
**		-> uses
**	8 : use file descriptor
**	~8 : use filename
*/
# define REDICT_LESS 11
# define REDICT_GREATER 1
# define REDICT_LLESS 6
# define REDICT_GGREATER 3
# define REDICT_PIPE 12
# define REDICT_LESS_AND 5
# define REDICT_GREATER_AND 6
# define REDICT_LESS_MINUS 7
# define REDICT_GREATER_MINUS 8
# define REDICT_LLESS_MINUS 9
# define REDICT_GGREATER_MINUS 10
# define REDICT_LESS_GREATER 11
# define REDICT_GREATER_PIPE 12

# define REDICT_N_TYPE 13
# define REDICT_IS_FD 0x100
# define REDICT_IS_FILENAME ~REDICT_IS_FD & 0x100
# define REDICT_SCL 
# define MASK_LAST 0x1
# define MASK_AFTER 0x10

/*
**	-> Redirection data
**
**	type		: redirection type
**	open_flag	: flags to send to open()
**	fd			: a file descriptor
**	filename	: a filename
*/
typedef struct			s_redirection
{
	int					type;
	int					init;
	int					open_flag;
	union
	{
		unsigned int	fd;
		t_word			*filename;
	};
}						t_redirection;

/*
**	=============================
**	========== COMMAND ==========
**	=============================
**
**	type	: command type
**	flag	: command specials
**	redir	: redirection if necessairy
**	...
**
*/
typedef struct 			s_command
{
	int					type;
	int					flag;
	t_redirection		*redir;
}						t_command;

/*
**	=================================
**	========== LEXER ITEMS ==========
**	=================================	
**
**	Everythink what a lexer item can be ! 
*/
typedef union			u_lexer_content
{
	t_word				*word;
	int					number;
	t_wordlist			*wlst;
	t_command			*command;
	t_redirection		*redirect;
}						t_lexer_content;

typedef struct			s_lexer_item
{
	union
	{
		t_word			*word;
		int				number;
		t_wordlist		*wlst;
		t_command		*command;
		t_redirection	*redir;
	};
	int					type;
}						t_lexer_item;

# define IS_LIST 0
# define IS_ITEM 1
# define PARSE_OP 0
# define PARSE_WORDLIST 1
/*
**	logical_value : Valeur a utiliser pour les operateurs logiques ("&&", "||", ...)
**
**	parse_type :	0 = op
**					1 = left
**					2 = right
**
**	word_left : Liste de mots pour le membre droit d'un operateur (commande avec ses arguments, nom de fichier, ...)
**		(si op == NULL seulment)
**	word_right : Lste de mots pour le membre droit d'un operateur (commande avec ses arguments, nom de fichier, ...)
**		(ssi op == NULL)
**
**	op : Operateur; il s'agit du <content> du mallion actuel
**		 (Redirection, Separateur, ...) en gros : tout sauf les mots
**
**	begin : le prochain noeud
**	end : le dernier noeud	
*/
typedef struct			s_parser
{
	int					logical_value;
	int					parse_type;
	union
	{
		t_dlist			*command;
		t_lexer_item	*op;
	};
	struct s_parser		*begin;
	struct s_parser		*end;
}						t_parser;

/*
**
**	Parse (ligne_de_commande)
**
**	Verifier(ligne_de_commande);
**	states = create_states(ligne_de_commande)
**
**	RECURSIF (states, last_node)
**	si states
**		verifier la grammaire (verifier la coordonance entre	<states -> content> et <states -> next -> content>)
**		\	-> si faux
**		|	|	afficher("Syntax error");
**		|	\	supprimer arbre ?
**		|	-> sinon
**		|	|	new_node = nouveau noeud
**		|	|				->
**		|	|				|	logical_value = 0;
**		|	|				|	parse_type = (item -> type) == IS_WORD;
**		|	|				\	-> si (item -> type) != IS_WORD
**		|	|				|	|	swap = last_node
**		|	|				|	|	(new_node -> begin) = last_node;  
**		|	|				|	|	(swap -> left) = new_node;
**		|	|				|	|	(new_node -> op) = item;
**		|	|				|	\	RECURSIF(get_next_operator(new_node), new_node))
**		|	|				|	-> sinon
**		|	|				|	|	(states -> last -> next) = NULL;
**		|	|				|	|	wordlist = rewind_words(&states->last);
**		|	|				|	\	(new_node -> command) = wordlist;
**		|	|				|
**		|	|				
**		\	|
**			
**
*/

t_redirection			*new_redirection(int type, int open_flag, void *dest);
t_redirection			*is_a_redirection(const char **s);
int						transit_form_redirection(t_lexer_item *last, t_redirection *r, t_lexer_item *next);
t_command				*new_command(int type, int flag, t_redirection *redir);
void					free_command(t_command **c);
t_word					*new_word(int is_dollard, int is_quote, int is_asign);
void					word_set_token(t_word *w, char *s, int len);
t_wordlist				*new_wordlist(t_word *w);
void					free_wordlist(t_wordlist **wlst);
t_lexer_item			*new_lexer_item(void *data, int type);
void					print_redir(t_redirection *r);
void					print_word(t_word *w);
t_word					*is_spec_character(char s, int *type);
t_word					*is_an_logical_operator(char *s, int *type);
t_word					*lexer_word(const char **s, int *type);
void					print_debug_states(t_dlist *s);
void					print_debug_item(t_lexer_item *it);
t_dlist					*create_states(const char *s);
void					free_item(t_lexer_item *it);
void	print_debug_tree(t_parser *s);
void	print_debug_node(t_parser *s);

#endif