#include <command.h>

static int			verification_redirection_list(t_list *lst)
{
	t_redirection	*r;

	while (lst)
	{
		r = (t_redirection*)lst->content;
		if (r->type != DCHEVRON_GAUCHE &&
			(!*r->filename || !ft_isprint(*r->filename)))
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

static int			verification_agregateur_list(t_list *lst)
{
	t_agregateur	*a;

	while (lst)
	{
		a = (t_agregateur*)lst->content;
		if (a->fd_2 == -1)
		{
			ft_putstr_fd(a->filename, 2);
			write(2, ": No such file or directory\n", 28);
			return (1);
		}
		else if (a->fd_2 >= MAX_AGR || a->fd_1 >= MAX_AGR)
		{
			ft_putnbr_fd((a->fd_1 >= MAX_AGR) ? a->fd_1 : a->fd_2, 2);
			write(2, ": Bad file descriptor\n", 22);
			return (1);
		}
		lst = lst->next;
	}
	return (0);
}

static int			verification_redirections(t_redirections *rs)
{
	if (verification_redirection_list(rs->normal) ||
		verification_agregateur_list(rs->agr))
		return (1);
	return (0);
}

int					verification_pipeline(t_list *pipeline)
{
	t_command		*c;

	while (pipeline)
	{
		c = pipeline->content;
		print_command(c);
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
