#include <command.h>

int				is_a_spec_char(int c)
{
	return (c == '|' || c == '<' || c == '>' || c == ';');
}

void			print_command(t_command *c)
{
	char		**args;

	printf("==== %p ===\n", c);
	args = c->argv;
	while (*args)
	{
		printf("%s\n", *args);
		args++;
	}
	printf("(%d %d %d)\n", ft_lstsize(c->redirs.in), ft_lstsize(c->redirs.out), ft_lstsize(c->redirs.err));
}

void		free_command(t_command *c)
{
	if (c)
	{
		end_redirections(&c->redirs);
		free_double_array(c->argv);
		free(c);
	}
}

void		reset_copy(char **cpy, char **str)
{
	*cpy = ft_strnew(1024);
	*str = *cpy;
}


t_list			*get_pipeline(char **s, t_env *e)
{
	t_list		*cmds;
	t_command	*c;

	cmds = NULL;
	c = NULL;
	while (**s && **s != ';')
	{
		while (**s == ' ')
			(*s)++;
		if (!is_a_spec_char(**s))
			c = get_command(s, e);
		else if (**s == '|')
		{
			if (!c)
			{
				write(2, "syntax error near unexpected token `|'", 38);
				(*s)++;
				break ;
			}
			(*s)++;
			ft_lstadd_end(&cmds, ft_lstnew_noalloc(c, sizeof(t_command)));
			c = NULL;
		}
	}
	if (c)
		ft_lstadd_end(&cmds, ft_lstnew_noalloc(c, sizeof(t_command)));
	return (cmds);
}

t_command		*get_command(char **s, t_env *e)
{
	t_command	*c;
	char		*cpy;
	char		*str;

	c = malloc(sizeof(t_command));
	str = ft_strnew(1024);
	cpy = str;
	if (c)
	{
		//printf("%s\n", *s);
		ft_bzero(c, sizeof(t_command));
		while (**s && !is_a_spec_char(**s) && !is_a_redirection(*s))
		{
			if (**s == ' ')
			{
				while (**s == ' ')
					(*s)++;
				if (*str)
				{
					ft_lstadd(&c->args, ft_lstnew(str, cpy - str + 2));
					free(str);
					str = ft_strnew(1024);
					cpy = str;
				}
			}
			else
				*(cpy++) = *((*s)++);
		}
		while (**s == ' ')
			(*s)++;
		while (is_a_redirection(*s))
		{
			c->need_redir = build_redirection(&c->redirs, s);
			while (**s == ' ')
				(*s)++;
		}
	}
	if (*str)
		ft_lstadd(&c->args, ft_lstnew(str, cpy - str + 2));
	free(str);
	c->argv = lst_to_tab(c->args);
	check_tilde_and_dollar(*e, c->argv, 1);
	//print_command(c);
	return (c);
}
