/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/02 17:32:00 by mfamilar          #+#    #+#             */
/*   Updated: 2015/12/02 17:32:02 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int	negative;
	int	i;
	int	nombre;

	negative = 0;
	nombre = 0;
	i = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' ||
			str[i] == '\v' || str[i] == '\r' || str[i] == '\f')
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		negative = 1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		nombre = nombre * 10 + str[i] - 48;
		i++;
	}
	if (negative == 1)
		return (-nombre);
	return (nombre);
}
