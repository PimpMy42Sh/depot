/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/02 17:58:16 by mfamilar          #+#    #+#             */
/*   Updated: 2015/12/02 17:58:19 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char *cdst;
	char *csrc;

	cdst = (char*)dst;
	csrc = (char*)src;
	if (csrc <= cdst)
	{
		cdst += len - 1;
		csrc += len - 1;
		while (len--)
			*cdst-- = *csrc--;
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
