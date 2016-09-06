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

	while (pipeline)
	{
		c = pipeline->content;
		if (!c)
		{
			write(2, "Need a valide command\n", 22);
			return (1);
		}
		if (!c->args)
		{
			write(2, "Need a valide command\n", 22);
			return (1);
		}
		//print_command(c);
		if (verification_redirections(&c->redirs))
			return (2);
		if (c->need_redir && !c->args)
		{
			write(2, "Need a valide command\n", 22);
			return (4);
		}
		pipeline = pipeline->next;
	}
	return (0);
}

static int				is_a_newline(t_it *it, char eof)
{
	int		delta;

	delta = (it->len + 2) / it->ws_col;
	move_begin(it);
	while (delta)
	{
		tputs(tgetstr(DOWN, NULL), 0, my_putchar);
		delta--;
	}
	if (it->line)
	{
		if (it->buffer == eof)
			return (0);
		ft_putendl(it->line);
	}
	else
		write(1, "\n", 1);
	return (1);
}

static char				*not_close(char **s, char eof, t_it *it)
{
	it->eof = 1;
	printf("%c\n", eof);
	if (verification_line(s, it))
	{
		ft_putstr("> ");
		resumed_terminal();
		while (read(0, &it->buffer, 4))
		{
			if ((it->buffer == CTRL_D && !it->len) || !it->eof)
				break ;
			parse_line(it);
			if (it->buffer == '\n')
			{
				if (!is_a_newline(it, eof))
					break ;
				it->i = 0;
				it->buffer = 0;
				it->len = 0;
				it->line = 0;
				ft_putstr("\n> ");
			}
			it->buffer = 0;
		}
		suspend_terminal();
	}
	it->eof = 0;
	return (NULL);
}

static char			check_eof(int ref)
{
	if (ref == BAD_QUOTES)
		return (39);
	if (ref == BAD_D_QUOTES)
		return (34);
	if (ref == BAD_B_QUOTES)
		return ('`');
	if (ref == BAD_PARENTHESE)
		return (')');
	if (ref == BAD_CROCHETS)
		return (']');
	if (ref == BAD_ACCOLADES)
		return ('}');
	return (0);
}

int					verification_line(char **s, t_it *it)
{
	int			i;
	char		eof;

	if ((i = check_line_is_close(*s)))
	{
		eof = check_eof(i);
		not_close(s, eof, it);
	}
	return (0);
}
