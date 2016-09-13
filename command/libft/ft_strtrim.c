/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/02 18:11:39 by mfamilar          #+#    #+#             */
/*   Updated: 2016/04/19 11:13:51 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	str = (char *)malloc(sizeof(char*) * ft_strlen(s - i));
	if (str == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		str[j] = s[i];
		i++;
		j++;
	}
	j--;
	while (str[j] == ' ' || str[j] == '\n' || str[j] == '\t')
	{
		str[j] = '\0';
		j--;
	}
	return (str);
}
