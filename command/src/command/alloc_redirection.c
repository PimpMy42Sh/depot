#include <command.h>

static void			end_agr(t_agregateur *a)
{
	if (a->fd_1 > 2)
		close(a->fd_1);
	if (a->fd_2 > 2)
		close(a->fd_2);
	free(a->filename);
	free(a);
}

static void			end_redirection(t_redirection *r)
{
	if (r->fd != -1)
		close(r->fd);
	if (r->stdfd > 2)
		close(r->stdfd);
	free(r->filename);
	free(r);
}

void				redirection_add(t_list **alst, t_redirection *new)
{
	int				ok;
	t_list			*tmp;
	t_redirection	*r;

	ok = 1;
	tmp = *alst;
	while (tmp)
	{
		r = (t_redirection*)tmp->content;
		if (r->stdfd == new->stdfd)
		{
			ok = 0;
			end_redirection(r);
			tmp->content = new;
			break ;
		}
		tmp = tmp->next;
	}
	if (ok)
		ft_lstadd(alst, ft_lstnew_noalloc(new, sizeof(t_redirection)));
}

t_redirection		*new_redirection(t_redirections *t, int fd, int type,
					char *filename)
{
	t_redirection	*r;

	r = (t_redirection*)malloc(sizeof(t_redirection));
	ft_memset(r, 0, sizeof(t_redirection));
	r->fd = -1;
	r->type = type;
	r->filename = filename;
	r->stdfd = fd;
	if (type == CHEVRON_DROIT)
		r->fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == DCHEVRON_DROIT)
		r->fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (type == CHEVRON_GAUCHE)
		r->fd = open(filename, O_RDONLY);
	else if (type == DCHEVRON_GAUCHE)
		prepare_hdoc(r);
	redirection_add(&t->normal, r);
	return (r);
}

void				end_redirections(t_redirections *redirs)
{
	t_list			*lst;
	t_list			*next;

	lst = redirs->agr;
	while (lst)
	{
		next = lst->next;
		end_agr(lst->content);
		free(lst);
		lst = next;
	}
	lst = redirs->normal;
	while (lst)
	{
		next = lst->next;
		end_redirection(lst->content);
		free(lst);
		lst = next;
	}
}
