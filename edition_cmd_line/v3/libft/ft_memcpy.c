/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/02 17:57:42 by mfamilar          #+#    #+#             */
/*   Updated: 2015/12/02 17:57:44 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char			*cdst;
	const unsigned char		*csrc;

	cdst = dst;
	csrc = src;
	while (n--)
		*cdst++ = *csrc++;
	return (dst);
}
