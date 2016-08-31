/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/02 11:39:51 by mfamilar          #+#    #+#             */
/*   Updated: 2015/12/03 17:59:58 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new_list;
	t_list	*begin;

	new_list = (*f)(lst);
	if (new_list == NULL)
		return (NULL);
	begin = new_list;
	while (lst->next != NULL)
	{
		lst = lst->next;
		new_list->next = (*f)(lst);
		if (new_list->next == NULL)
			return (NULL);
		new_list = new_list->next;
	}
	return (begin);
}
