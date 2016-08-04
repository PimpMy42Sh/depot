/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 10:27:14 by mfamilar          #+#    #+#             */
/*   Updated: 2016/04/26 16:16:45 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdlib.h"

char			*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		len;

	str = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	if (len >= 0 && (str = (char *)malloc(sizeof(*str) * (len + 1))))
	{
		ft_strcpy(str, s1);
		ft_strcat(str, s2);
	}
	return (str);
}
