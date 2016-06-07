/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 20:01:26 by mfamilar          #+#    #+#             */
/*   Updated: 2015/12/04 14:33:45 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

char	*ft_strrev(char *s1)
{
	char	*s2;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(s1);
	s2 = (char *)malloc(sizeof(char *) * len + 1);
	len--;
	while (len >= 0)
	{
		s2[i] = s1[len];
		i++;
		len--;
	}
	s2[i] = '\0';
	return (s2);
}
