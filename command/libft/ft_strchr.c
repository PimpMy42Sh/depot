/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/02 18:02:25 by mfamilar          #+#    #+#             */
/*   Updated: 2015/12/02 18:02:29 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*str;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			str = (char *)&s[i];
			return (str);
		}
		i++;
	}
	if (s[i] == '\0' && c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}
