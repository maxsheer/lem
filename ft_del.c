/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlynesse <tlynesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 13:19:47 by tlynesse          #+#    #+#             */
/*   Updated: 2019/12/07 13:20:15 by tlynesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	del_link(t_link **link)
{
	t_link	*tmp;
	t_link	*next;

	tmp = *link;
	while (tmp)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	*link = NULL;
}

void	del_rooms(t_room **room)
{
	t_room	*tmp;
	t_room	*next;

	tmp = *room;
	while (tmp)
	{
		next = tmp->next;
		del_link(&tmp->link);
		if (tmp->in == 0)
			free(tmp->name);
		free(tmp);
		tmp = next;
	}
	*room = NULL;
}
