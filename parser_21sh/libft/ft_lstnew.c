/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/02 11:41:17 by mfamilar          #+#    #+#             */
/*   Updated: 2015/12/02 17:48:29 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*element;

	element = (t_list*)malloc(sizeof(t_list));
	if (element == NULL)
		return (NULL);
	if (content == NULL)
	{
		element->content = NULL;
		element->content_size = 0;
	}
	else
	{
		element->content = (t_list*)malloc(content_size);
		if (element->content == NULL)
			return (NULL);
		ft_memcpy(element->content, content, content_size);
		element->content_size = content_size;
	}
	element->next = NULL;
	return (element);
}
