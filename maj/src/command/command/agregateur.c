/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   agregateur.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 11:50:38 by fjacquem          #+#    #+#             */
/*   Updated: 2016/09/22 11:50:39 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <command.h>

void		do__agr_close(t_list *lst)
{
	t_agregateur		*a;

	while (lst)
	{
		a = (t_agregateur*)lst->content;
		if (a->close)
			close(a->fd_1);
		lst = lst->next;
	}
}

void		do__agr_dup(t_list *lst)
{
	t_agregateur		*a;

	while (lst)
	{
		a = (t_agregateur*)lst->content;
		if (!a->close)
			dup2(a->fd_2, a->fd_1);
		lst = lst->next;
	}
}
