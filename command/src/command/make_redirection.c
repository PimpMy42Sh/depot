#include <command.h>

/*
**	Execute une/des redirection(s)
**
**	in:		stdin (ou duplicat)
**	out:	stdout (ou duplicat)
**	lst:	liste de redirection
*/

static void		do__redirection(int in, int out, t_list *lst)
{
	t_redirection	*r;

	while (lst)
	{
		r = (t_redirection*)lst->content;
		if (r->stdfd == 1)
			dup2(r->fd, out);
		else if (r->stdfd == 0)
			dup2(r->fd, in);
		else
			dup2(r->fd, r->stdfd);
		close(r->fd);
		lst = lst->next;
	}
}

/*
**	Execute les redirections requises
**
**	redirs:	donnees de redirections
**	in:		stdin (ou duplicat)
**	out:	stdout (ou duplicat)
*/

void			do_redirections(t_redirections *redirs, int in, int out)
{
	do__agr_close(redirs->agr);
	do__redirection(in, out, redirs->normal);
	do__agr_dup(redirs->agr);
}
