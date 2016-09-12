#include <command.h>

static void		realloc_copy(char **cpy, char **str)
{
	char		*tmp;

	if (*cpy - *str >= 1023)
	{
		tmp = ft_strnew(1024 + (*cpy - *str) + 1);
		ft_strcpy(tmp, *str);
		free(*str);
		*str = tmp;
		*cpy = *str;
	}
}

static void		argument(t_command *c, char **s, char **cpy, char **str)
{
	while (**s == ' ')
		(*s)++;
	if (*str)
	{
		ft_lstadd(&c->args, ft_lstnew(*str, *cpy - *str + 2));
		free(*str);
		*str = ft_strnew(1024);
		*cpy = *str;
	}
}

static void		redirection(t_command *c, char **s)
{
	c->need_redir = build_redirection(&c->redirs, s);
	while (**s == ' ')
		(*s)++;
}

static void		end__get_command(t_env *e, t_command *c, char *str, char *cpy)
{
	if (*str)
		ft_lstadd(&c->args, ft_lstnew(str, cpy - str + 2));
	free(str);
	c->argv = lst_to_tab(c->args);
	check_tilde_and_dollar(e->environ, c->argv, 0);
}

t_command		*get_command(char **s, t_env *e)
{
	t_command	*c;
	char		*cpy;
	char		*str;

	str = ft_strnew(1024);
	cpy = str;
	if ((c = (t_command*)malloc(sizeof(t_command))))
	{
		ft_bzero(c, sizeof(t_command));
		while ((**s && !is_a_spec_char(**s)) || is_a_redirection(*s))
			if (**s == ' ')
				argument(c, s, &cpy, &str);
			else if (is_a_redirection(*s))
				redirection(c, s);
			else
			{
				realloc_copy(&cpy, &str);
				*(cpy++) = *((*s)++);
			}
		while (**s == ' ')
			(*s)++;
	}
	end__get_command(e, c, str, cpy);
	return (c);
}
