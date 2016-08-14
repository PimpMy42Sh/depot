/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/10 16:42:03 by mfamilar          #+#    #+#             */
/*   Updated: 2016/07/11 14:39:28 by Marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void		no_such_file(char *path)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": No such file or directory.\n", 2);
	ft_putstr_fd(RESET, 2);
}
