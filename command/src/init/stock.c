#include <minishell.h>

t_it		*ft_stock_it(t_it *it)
{
	static t_it	*tmp = NULL;

	if (it)
		tmp = it;
	return (tmp);
}

t_ctrl_c	*ft_stock_ctrl_c(t_ctrl_c *ctrl_c)
{
	static t_ctrl_c	*tmp = NULL;

	if (ctrl_c)
		tmp = ctrl_c;
	return (tmp);
}

t_tty		*ft_stock_term(t_tty *tty)
{
	static t_tty	*tmp = NULL;

	if (tty)
		tmp = tty;
	return (tmp);
}
