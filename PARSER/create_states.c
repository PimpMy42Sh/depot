#include <grammar.h>

static t_lexer_item		*create_state(const char **s)
{
	t_lexer_item	*item;
	void			*data;
	int				wtype;

	while (ft_isspace(**s))
		(*s)++;
	if ((data = is_a_redirection(s)))
		item = new_lexer_item(data, IS_REDIRECTION);
	else
	{
		wtype = 0;
		data = lexer_word(s, &wtype);
		item = new_lexer_item(data, wtype);
	}
	return (item);
}

t_dlist					*create_states(const char *s)
{
	t_dlist	*new;
	t_dlist	*item_list;

	item_list = NULL;
	while (*s)
	{
		printf("%s\n", s);
		new = ft_dlstnew(NULL, 0);
		new->content = (t_lexer_item*)create_state(&s);
		new->content_size = sizeof(t_lexer_item);
		ft_dlstadd_end(&item_list, new);
	}
	return (item_list);
}
