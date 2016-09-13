#include <command.h>

static int		alloc_size()
{
	t_it		*it;

	it = ft_stock_it(0);
	return (it->len);
}

static void		realloc_copy(char **s, char **str, int *len)
{
	*(*str + *len) = **s;
	(*s)++;
	(*len)++;
}

static void		argument(t_command *c, char **s, t_norme_command *n)
{
	while (**s == ' ')
		(*s)++;
	if (*n->str)
	{
		ft_lstadd(&c->args,
		ft_lstnew(n->str, n->len + 1));
		free(n->str);
		n->str = ft_strnew(alloc_size());
		n->len = 0;
	}
}

static void		redirection(t_command *c, char **s)
{
	c->need_redir = build_redirection(&c->redirs, s);
	while (**s == ' ')
		(*s)++;
}

static void		end__get_command(t_env *e, t_command *c, t_norme_command *n)
{
	if (*n->str)
		ft_lstadd(&c->args,
		ft_lstnew(n->str, n->len + 1));
	free(n->str);
	c->argv = lst_to_tab(c->args);
	check_tilde_and_dollar(e->environ, c->argv, 0);
}

static void		quotes(t_norme_command *n, char **s)
{
	int		tmp;

	tmp = **s;
	realloc_copy(s, &n->str, &n->len);
	while (**s != tmp)
		realloc_copy(s, &n->str, &n->len);
	realloc_copy(s, &n->str, &n->len);
}

t_command		*get_command(char **s, t_env *e)
{
	t_command		*c;
	t_norme_command	n;

	n.str = ft_strnew(alloc_size());
	n.len = 0;
	if ((c = (t_command*)malloc(sizeof(t_command))))
	{
		ft_bzero(c, sizeof(t_command));
		while ((**s && !is_a_spec_char(**s)) || is_a_redirection(*s))
			if (**s == ' ')
				argument(c, s, &n);
			else if (is_a_redirection(*s))
				redirection(c, s);
			else if (**s == '\"' || **s == '\'')
				quotes(&n, s);
			else
				realloc_copy(s, &n.str, &n.len);
		while (**s == ' ')
			(*s)++;
	}
	end__get_command(e, c, &n);
	return (c);
}
