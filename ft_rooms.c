/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rooms.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlynesse <tlynesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 13:30:22 by tlynesse          #+#    #+#             */
/*   Updated: 2019/12/07 13:30:23 by tlynesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room	*roomnew(char *name, t_point coords, t_link *link)
{
	t_room	*room;

	if (!(room = (t_room *)malloc(sizeof(t_room))))
		exit_w(-1);
	room->name = name;
	room->coords = coords;
	room->dist = INFINITY;
	room->in = 0;
	room->out = 0;
	room->links = 0;
	room->link = link;
	room->next = NULL;
	return (room);
}

t_room	*getroomout(t_room *room)
{
	t_room	*out;
	t_link	*tmp;

	out = roomnew(room->name, room->coords, NULL);
	out->out = 1;
	tmp = room->link;
	while ((tmp))
	{
		add_link(&out->link, init_link(tmp->room, 1));
		tmp = tmp->next;
	}
	rev_link1(&out->link);
	return (out);
}

t_room	*getroomin(t_room *room)
{
	t_room	*in;
	t_link	*tmp;

	in = room;
	in->in = 1;
	in->links = 1;
	tmp = in->link;
	while (tmp)
	{
		tmp->weight = INFINITY;
		tmp = tmp->next;
	}
	return (in);
}

t_room	*getsplitroom(t_room *room)
{
	t_room	*in;
	t_room	*out;

	in = getroomin(room);
	out = getroomout(room);
	add_link(&in->link, init_link(out, 0));
	add_link(&out->link, init_link(in, INFINITY));
	out->next = in->next;
	in->next = out;
	return (in);
}

void	splitrooms(t_room **room, t_room *start, t_room *end)
{
	t_room	*tmp;

	tmp = *room;
	while (tmp)
	{
		if (tmp != start && tmp != end)
		{
			tmp = getsplitroom(tmp);
			tmp = tmp->next->next;
		}
		else
			tmp = tmp->next;
	}
	link_comp(room, start, end);
}
