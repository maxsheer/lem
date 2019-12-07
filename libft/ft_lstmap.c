/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 21:24:46 by aromny-w          #+#    #+#             */
/*   Updated: 2018/12/12 21:24:48 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	del(void *elem, size_t size)
{
	size = 0;
	free(elem);
}

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list		*list;
	t_list		*list_ptr;

	list = f(lst);
	list_ptr = list;
	while ((lst = lst->next))
	{
		if (!(list_ptr->next = f(lst)))
		{
			ft_lstdel(&list, del);
			return (NULL);
		}
		list_ptr = list_ptr->next;
	}
	return (list);
}
