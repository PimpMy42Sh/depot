/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/02 11:42:10 by mfamilar          #+#    #+#             */
/*   Updated: 2015/12/02 11:42:24 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*cs;
	unsigned char	cc;

	i = 0;
	cc = c;
	cs = (unsigned char *)s;
	while (i < n)
	{
		if (cs[i] == cc)
			return ((void*)s + i);
		i++;
	}
	return (NULL);
}
