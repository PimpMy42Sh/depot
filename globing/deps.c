#include "../command/libft/libft.h"

t_list		*ft_lstnew_noalloc(const void *cnt, size_t cnt_size)
{
	t_list	*new;

	new = ft_memalloc(sizeof(t_list));
	new->content = (void*)cnt;
	new->content_size = cnt_size;
	return (new);
}

int			ft_strcasecmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && ft_tolower(*s1) == ft_tolower(*s2))
		s1++;
		s2++;
	return (*s2 - *s1);
}