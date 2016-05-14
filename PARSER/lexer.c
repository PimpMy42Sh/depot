#include <grammar.h>

t_lexer_item	*new_lexer_item(void *data, int type)
{
	t_lexer_item	*lex_i;

	if ((lex_i = (t_lexer_item*)malloc(sizeof(t_lexer_item))))
	{
		if (type == IS_WORD)
			lex_i->word = (t_word*)data;
		else if (type == IS_NUMBER)
			lex_i->number = *(int*)data;
		else if (type == IS_WORDLIST)
			lex_i->wlst = (t_wordlist*)data;
		else if (type == IS_COMMAND)
			lex_i->command = (t_command*)data;
		else if (type == IS_REDIRECTION)
			lex_i->redir = (t_redirection*)data;
		else if (type == IS_OPERATOR)
			lex_i->word = (t_word*)data;
		else
			write(1, "Parsing error : undefined lexer_item type\n", 37);
		lex_i->type = type;
	}
	return (lex_i);
}

static int	unaccpectable(char c)
{
	return (
			c == '(' || c == ')' ||
			c == '&' || c == '|' ||
			c == '>' || c == '<' ||
			c == ';' || c == ' ' ||
			c == '\t'
	);
}

t_word		*is_an_logical_operator(char *s, int *type)
{
	static char		*ops[] = {"&&", "||", "==", "!=", NULL};
	char			word[3];
	int				index;
	t_word			*w;

	w = NULL;
	index = 0;
	word[2] = 0;
	while (ops[index] && ft_strncmp(ops[index], s, 2))
		index++;
	if (ops[index])
	{
		word[0] = *s;
		word[1] = *(s + 1);
		w = new_word(0, 0, 0);
		word_set_token(w, (char*)word, 1);
		*type = IS_OPERATOR;
		w->type = 0;
	}
	return (w);
}

t_word		*is_spec_character(char s, int *type)
{
	static char		*ops = "();\\";
	char			word[2];
	t_word			*w;

	w = NULL;
	if (ft_strchr(ops, s))
	{
		word[0] = s;
		word[1] = 0;
		w = new_word(0, 0, 0);
		word_set_token(w, (char*)word, 1);
		*type = IS_OPERATOR;
		w->type = 0;
	}
	return (w);
}

t_word		*lexer_word(const char **s, int *type)
{
	char			word[256];
	int				i;
	t_word			*w;

	i = 1;
	if (!(w = is_spec_character(**s, type)))
	{
		if (**s == '$')
		{
			word[0] = '$';
			i = 1;
			(*s)++;		
		}	
		else
			i = 0;
		while ((**s) && !unaccpectable(**s))
			word[i++] = *((*s)++);
		word[i] = 0;
		w = new_word(word[0] == '$',
			word[0] == '\"' || word[0] == '\'' || word[0] == '`',
			word[0] == '=');
		word_set_token(w, (char*)word, i);
		*type = IS_WORD;
	}
	else
		(*s)++;
	return (w);
}
