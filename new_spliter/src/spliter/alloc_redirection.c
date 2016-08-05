/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <fjacquem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 10:16:42 by fjacquem          #+#    #+#             */
/*   Updated: 2016/08/04 16:20:45 by Marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <spliter.h>

t_redirection		*new_redirection_err(t_redirections *t, int type,
					char *filename)
{
	t_redirection	*r;

	r = (t_redirection*)malloc(sizeof(t_redirection));
	ft_memset(r, 0, sizeof(t_redirection));
	r->fd = -1;
	r->type = type;
	r->filename = filename;
	if (type == CHEVRON_DROIT)
	{
		r->fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		ft_lstadd(&t->err, ft_lstnew_noalloc(r, sizeof(t_redirection)));
	}
	else if (type == DCHEVRON_DROIT)
	{
		r->fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		ft_lstadd(&t->err, ft_lstnew_noalloc(r, sizeof(t_redirection)));
	}
	return (r);
}

t_redirection		*new_redirection(t_redirections *t, int type,
					char *filename)
{
	t_redirection	*r;

	r = (t_redirection*)malloc(sizeof(t_redirection));
	ft_memset(r, 0, sizeof(t_redirection));
	r->fd = -1;
	r->type = type;
	r->filename = filename;
	if (type == CHEVRON_DROIT)
	{
		r->fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		ft_lstadd(&t->out, ft_lstnew_noalloc(r, sizeof(t_redirection)));
	}
	else if (type == DCHEVRON_DROIT)
	{
		r->fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		ft_lstadd(&t->out, ft_lstnew_noalloc(r, sizeof(t_redirection)));
	}
	else if (type == CHEVRON_GAUCHE)
	{
		r->fd = open(filename, O_RDONLY | O_APPEND);
		ft_lstadd(&t->in, ft_lstnew_noalloc(r, sizeof(t_redirection)));
	}
	else if (type == DCHEVRON_GAUCHE)
		prepare_hdoc(t, r);
	return (r);
}

void				end_redirection(t_redirection *r)
{
	if (r->fd != -1)
		close(r->fd);
	free(r->filename);
	free(r);
}

void				end_redirections(t_redirections *redirs)
{
	t_list			*lst;
	t_list			*next;

	redirs->fd_in = 0;
	redirs->fd_out = 0;
	lst = redirs->in;
	while (lst)
	{
		next = lst->next;
		end_redirection(lst->content);
		free(lst);
		lst = next;
	}
	lst = redirs->out;
	while (lst)
	{
		next = lst->next;
		end_redirection(lst->content);
		free(lst);
		lst = next;
	}
}
