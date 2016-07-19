/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/02 16:00:20 by mfamilar          #+#    #+#             */
/*   Updated: 2016/04/21 09:33:41 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_intlen(int n)
{
	int	i;

	i = 1;
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	if (n >= 0 && n <= 9)
		return (i);
	if (n >= 10)
	{
		while (n >= 10)
		{
			n = n / 10;
			i++;
		}
	}
	return (i);
}

char			*ft_itoa(int n)
{
	char	*s;
	int		i;

	i = ft_intlen(n);
	s = ft_strnew(i);
	if (s == NULL)
		return (NULL);
	if (n < 0)
	{
		n *= -1;
		s[0] = '-';
	}
	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	while (n > 0)
	{
		s[--i] = (n % 10) + 48;
		n = n / 10;
	}
	return (s);
}
