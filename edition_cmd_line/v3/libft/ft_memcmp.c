/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/02 11:42:36 by mfamilar          #+#    #+#             */
/*   Updated: 2015/12/02 11:42:56 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*cs1;
	unsigned char	*cs2;
	int				ret;

	cs1 = (unsigned char*)s1;
	cs2 = (unsigned char*)s2;
	ret = 0;
	while (n-- && ret == 0)
		ret = (*cs1++) - (*cs2++);
	return (ret);
}
