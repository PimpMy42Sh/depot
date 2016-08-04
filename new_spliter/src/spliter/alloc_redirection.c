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
#include "../../include/minishell.h"


void				use_agregator_redirection(t_redirections *r, int fd_in, int fd_out)
{
	if (fd_out)
		r->fd_out |= 1 << fd_out;
	if (fd_in)
		r->fd_in |= 1 << fd_in;
}

t_redirection		*new_redirection(t_redirections *t, int type, char *filename)
{
	t_redirection	*r;
	t_it					*it;

	it = init_it_struct();
	r = (t_redirection*)malloc(sizeof(t_redirection));
	ft_memset(r, 0, sizeof(t_redirection));
	r->type = type;
	r->filename = filename;
	if (type == CHEVRON_DROIT)
		r->fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == DCHEVRON_DROIT)
		r->fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (type == CHEVRON_GAUCHE)
		r->fd = open(filename, O_RDONLY | O_CREAT | O_APPEND, 0644);
	else
	{
		r->fd = 0;
		printf("HEREDOC\n");
		it->eof = 1;
		ft_putstr("> ");
		while (read(0, &it->buffer, 4))
		{
			parse_line(it);
			if (it->buffer == '\n')
			{
				if (it->line)
				{
					if (!ft_strcmp(it->line, filename))
						break ;
					it->i = 0;
					it->len = 0;
					ft_lstadd(&t->hdoc, ft_lstnew(it->line, ft_strlen(it->line)));
					it->line = 0;
				}
				ft_putstr("\n> ");
			}
			it->buffer = 0;
		}
		it->eof = 0;
	}
	printf("FD = %d, %s\n", r->fd, filename);
	if (type & 1)
		ft_lstadd(&t->out, ft_lstnew_noalloc(r, sizeof(t_redirection)));
	else
		ft_lstadd(&t->in, ft_lstnew_noalloc(r, sizeof(t_redirection)));
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
