/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 17:10:34 by mfamilar          #+#    #+#             */
/*   Updated: 2016/07/08 18:25:32 by Marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 4096

# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>

typedef	struct	s_var
{
	int			read_end;
	size_t		j;
	int			a;
	int			ok;
}				t_var;

int				get_next_line(int const fd, char **line);
#endif
