/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 14:41:27 by mfamilar          #+#    #+#             */
/*   Updated: 2015/12/02 17:50:02 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	char				*cdst;
	char				*csrc;
	size_t				i;

	cdst = (char *)dst;
	csrc = (char *)src;
	i = 0;
	while (i < n)
	{
		if (csrc[i] == c)
		{
			cdst[i] = csrc[i];
			return (dst + i + 1);
		}
		cdst[i] = csrc[i];
		i++;
	}
	return (NULL);
}
