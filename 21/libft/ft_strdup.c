/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/02 18:04:03 by mfamilar          #+#    #+#             */
/*   Updated: 2016/07/04 20:07:13 by Marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*str;
	int		len;

	len = ft_strlen(src) + 1;
	str = ft_memalloc(sizeof(char) * len);
	return (!str ? NULL : ft_memcpy(str, src, len));
}
