/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/02 18:10:46 by mfamilar          #+#    #+#             */
/*   Updated: 2015/12/02 18:10:48 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			str = (char *)&s[i];
		}
		i++;
	}
	if (s[i] == '\0' && c == '\0')
		return ((char *)&s[i]);
	if (str != NULL)
		return (str);
	return (NULL);
}
