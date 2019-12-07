/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_algs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlynesse <tlynesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 13:16:12 by tlynesse          #+#    #+#             */
/*   Updated: 2019/12/07 14:02:11 by tlynesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			*depth_search(t_map *map, t_path *new, t_path tmp, t_room *room)
{
	t_link	*link;

	add_way(&tmp.way, init_way(room));
	tmp.len++;
	if (tmp.len > map->depth || !room || (new->way && new->len < tmp.len) ||
		tmp.len > room->dist)
		return (free_ways(&tmp, NULL));
	else if (tmp.way->room == map->end && (!new->way || tmp.len < new->len))
	{
		room->dist = tmp.len;
		best_path(&new, &tmp, map);
		return (free_ways(&tmp, NULL));
	}
	room->dist = tmp.len;
	link = tmp.way->room->link;
	while (link)
	{
		if (link->weight != INFINITY)
			depth_search(map, new, tmp, link->room);
		link = link->next;
	}
	return (free_ways(&tmp, NULL));
}

t_path			*path_finder(t_map *map, t_path *path, size_t k)
{
	t_path	new;

	ft_memset(&new, 0, sizeof(t_path));
	height_init(&map->room);
	rev_paths(path, new, k - 1);
	depth_search(map, &new, new, map->start);
	rev_paths(path, new, k - 1);
	if (!new.way)
		return (NULL);
	if (check_overlap(new))
	{
		dis_paths(path, k);
		return (path_finder(map, path, k));
	}
	else if (path_add(path, new, k) < k)
		return (path_finder(map, path, k));
	return (path);
}

void			solver(t_map map, size_t max)
{
	t_path	*path[1 + max];
	size_t	k;

	k = 0;
	path[k] = NULL;
	splitrooms(&map.room, map.start, map.end);
	while (++k <= max)
	{
		if (!(path[k] = path_eval(&map, path[k - 1], k)) ||
		!brakingsystem(path[k], path[k - 1], k, map.ants))
			break ;
	}
	if (k != 1)
	{
		writeinput(map.input);
		antsdist(path[k - 1], k - 1, map.ants);
	}
	map_delete(&map, path, k);
}

static t_path	*tryagain(t_map *map, t_path *init, size_t k)
{
	map->depth = INFINITY;
	return (path_eval(map, init, k));
}

t_path			*path_eval(t_map *map, t_path *init, size_t k)
{
	t_path	*path;
	size_t	i;

	i = -1;
	if (!(path = (t_path *)malloc(sizeof(t_path) * k)))
		exit_w(-1);
	while (++i < k - 1 && init)
	{
		path[i].way = init[i].way;
		path[i].len = init[i].len;
		path[i].limit = init[i].limit;
	}
	ft_memset(&path[i], 0, sizeof(path[i]));
	if (!path_finder(map, path, k))
	{
		free(path);
		if (k == 1 && map->depth != INFINITY)
			return (tryagain(map, init, k));
		return (NULL);
	}
	return (path);
}
