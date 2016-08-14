/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/02 17:56:59 by mfamilar          #+#    #+#             */
/*   Updated: 2015/12/02 17:57:01 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*element;

	element = (void *)malloc(size);
	if (element == NULL)
		return (NULL);
	else
		ft_bzero(element, size);
	return (element);
}
