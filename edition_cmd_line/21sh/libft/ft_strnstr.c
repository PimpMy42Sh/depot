/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/02 11:48:56 by mfamilar          #+#    #+#             */
/*   Updated: 2015/12/02 11:52:20 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t		i;
	int			j;

	i = 0;
	j = 0;
	if (!ft_strlen((char *)s2))
		return ((char *)s1);
	while (i < n && s1[i] != '\0')
	{
		if (s1[i + j] == s2[j])
		{
			while (s1[i + j] == s2[j] && (i + j) < n)
			{
				if (s2[j + 1] == '\0')
					return ((char *)s1 + i);
				j++;
			}
		}
		j = 0;
		i++;
	}
	return (NULL);
}
