#include "libft.h"

void	ft_dlstprinthead(t_dlist **head)
{
	t_dlist	*ptr;

	ptr = *head;
	while (ptr)
	{
		ft_putendl((char *)ptr->data);
		ptr = ptr->next;
	}
}

void	ft_dlstprinttail(t_dlist **tail)
{
	t_dlist	*ptr;

	ptr = *tail;
	while (ptr->prev)
	{
		ft_putendl((char *)ptr->data);
		ptr = ptr->prev;
	}
}

int		ft_dlstiter(t_dlist **head)
{
	t_dlist	*ptr;
	int		count;

	count = 0;
	ptr = *head;
	while (ptr)
	{
		count++;
		ptr = ptr->next;
	}
	return (count);
}
