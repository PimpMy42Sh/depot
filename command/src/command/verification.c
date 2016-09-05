#include <command.h>

static int			verification_redirection_list(t_list *lst)
{
	t_redirection	*r;

	while (lst)
	{
		r = (t_redirection*)lst->content;
		if (r->type != DCHEVRON_GAUCHE && (!*r->filename || !ft_isprint(*r->filename)))
		{
			write(2, "Need a filename\n", 16);
			return (1);
		}
		else if (r->fd == -1)
		{
			ft_putstr_fd(r->filename, 2);
			write(2, ": No such file or directory\n", 28);
			return (1);
		}
		lst = lst->next;
	}
	return (0);
}

static int			verification_redirections(t_redirections *rs)
{
	if (verification_redirection_list(rs->in) ||
		verification_redirection_list(rs->out) ||
		verification_redirection_list(rs->err))
		return (1);
	return (0);
}

int			verification_pipeline(t_list *pipeline)
{
	t_command		*c;
	t_command		*last_c;

	last_c = NULL;
	while (pipeline)
	{
		c = pipeline->content;
		if (!c)
		{
			write(2, "Need a valide command\n", 22);
			return (1);
		}
		//print_command(c);
		if (verification_redirections(&c->redirs))
			return (2);
		/*if (last_c && !c->argv)
		{
			write(2, "Need a valid command after a '|'\n", 27);
			return (3);
		}*/
		if (c->need_redir && !c->args)
		{
			write(2, "Need a valide command\n", 22);
			return (4);
		}
		last_c = c;
		pipeline = pipeline->next;
	}
	return (0);
	(void)last_c;
}

int					verification_line(char *s)
{
	return (check_parentheses(s) || check_line_is_close(s));
}
