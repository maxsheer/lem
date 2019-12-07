/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlynesse <tlynesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 13:26:49 by tlynesse          #+#    #+#             */
/*   Updated: 2019/12/07 13:27:04 by tlynesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_way	*init_way(t_room *room)
{
	t_way	*way;

	if (!(way = (t_way *)malloc(sizeof(t_way))))
		exit_w(-1);
	way->room = room;
	way->next = NULL;
	return (way);
}

void	map_init(t_map *map)
{
	map->ants = -1;
	map->room = NULL;
	map->start = NULL;
	map->end = NULL;
	map->input = NULL;
	map->buf = NULL;
	map->depth = 200;
}

void	height_init(t_room **room)
{
	t_room	*tmp;

	tmp = *room;
	while (tmp)
	{
		tmp->dist = INFINITY;
		tmp = tmp->next;
	}
}

t_link	*init_link(t_room *room, float weight)
{
	t_link *link;

	if (!(link = (t_link *)malloc(sizeof(t_link))))
		exit_w(-1);
	link->room = room;
	link->weight = weight;
	link->next = NULL;
	return (link);
}
