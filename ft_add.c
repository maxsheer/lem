/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlynesse <tlynesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 13:15:34 by tlynesse          #+#    #+#             */
/*   Updated: 2019/12/07 13:16:00 by tlynesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	add_link(t_link **link, t_link *new)
{
	new->next = *link;
	*link = new;
}

void	add_room(t_room **room, t_room *new)
{
	new->next = *room;
	*room = new;
}

size_t	path_add(t_path *path, t_path new, size_t k)
{
	size_t	i;

	i = 0;
	if (path)
		while (i < k - 1 && path[i].way)
			i++;
	path[i].way = new.way;
	path[i].len = new.len;
	path_sort(path, k);
	return (++i);
}

void	add_way(t_way **way, t_way *new)
{
	new->next = *way;
	*way = new;
}

void	linker(t_room *room_1, t_room *room_2)
{
	add_link(&room_1->link, init_link(room_2, 1));
	add_link(&room_2->link, init_link(room_1, 1));
	room_1->links++;
	room_2->links++;
}
