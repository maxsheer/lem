/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_comp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlynesse <tlynesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 13:18:17 by tlynesse          #+#    #+#             */
/*   Updated: 2019/12/07 13:18:18 by tlynesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	rooml_comp(t_link **link, t_room *end)
{
	t_link	*tmp;
	t_link	*new;
	t_link	*del;

	new = NULL;
	tmp = *link;
	if (tmp->room->in)
		add_link(&new, init_link(tmp->room->link->room, INFINITY));
	while (tmp->next)
	{
		if (tmp->next->room->in || tmp->next->room == end)
		{
			del = tmp->next;
			if (tmp->next->room->in)
				add_link(&new, init_link(tmp->next->room->link->room, \
				INFINITY));
			tmp->next = tmp->next->next;
			free(del);
		}
		else
			tmp = tmp->next;
	}
	rev_link1(&new);
	tmp->next = new;
}

static void	el_comp(t_link **link, t_room *start)
{
	t_link	*tmp;
	t_link	*new;

	new = NULL;
	tmp = *link;
	if (tmp->room->in)
		add_link(&new, init_link(tmp->room->link->room, INFINITY));
	else if (tmp->room == start)
		add_link(&new, init_link(tmp->room, INFINITY));
	while (tmp->next)
	{
		if (tmp->next->room->in)
			add_link(&new, init_link(tmp->next->room->link->room, INFINITY));
		else if (tmp->next->room == start)
			add_link(&new, init_link(tmp->next->room, INFINITY));
		tmp = tmp->next;
	}
	rev_link1(&new);
	del_link(link);
	*link = new;
}

static void	sl_comp(t_link **link)
{
	return ((void)link);
}

void		link_comp(t_room **room, t_room *start, t_room *end)
{
	t_room	*tmp;

	tmp = *room;
	while (tmp)
	{
		if (tmp->link && tmp == start)
			sl_comp(&tmp->link);
		else if (tmp->link && tmp == end)
			el_comp(&tmp->link, start);
		else if (tmp->in && tmp->link)
			rooml_comp(&tmp->link, end);
		tmp = tmp->next;
	}
}
