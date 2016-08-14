/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/02 18:11:10 by mfamilar          #+#    #+#             */
/*   Updated: 2015/12/02 18:11:11 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *s1, const char *s2)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!ft_strlen((char *)s2))
		return ((char *)s1);
	while (s1[i] != '\0')
	{
		if (s1[i + j] == s2[j])
		{
			while (s1[i + j] == s2[j] && s2[j] != '\0')
			{
				if (s2[j + 1] == '\0')
					return ((char *)s1 + i);
				j++;
			}
		}
		i++;
		j = 0;
	}
	return (NULL);
}
