/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlynesse <tlynesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 13:30:30 by tlynesse          #+#    #+#             */
/*   Updated: 2019/12/07 13:32:41 by tlynesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	set_truelen(t_path *path, int k)
{
	int	i;

	i = -1;
	while (++i < k)
		path[i].len = path[i].len / 2;
}

static void	set_limits(t_path *path, int k, int ants)
{
	int	i;
	int	threshold;

	threshold = path[0].len;
	while (ants)
	{
		i = -1;
		while (ants && ++i < k)
		{
			if (path[i].len + path[i].limit == threshold)
			{
				path[i].limit++;
				ants--;
			}
		}
		threshold++;
	}
}

void		antsdist(t_path *path, int k, int ants)
{
	t_ant	ant[ants];
	int		lines;
	int		i;
	int		n;

	ft_memset(ant, 0, sizeof(ant));
	set_truelen(path, k);
	set_limits(path, k, ants);
	n = 0;
	lines = path[0].len + path[0].limit;
	while (ants)
	{
		i = -1;
		while (++i < k)
		{
			if (path[i].limit && n < ants)
			{
				ant[n].number = n + 1;
				ant[n++].way = path[i].way->next;
				path[i].limit--;
			}
		}
		if (!printants(ant, ants))
			break ;
	}
}

void		setlink(char *line, t_map *map)
{
	t_room	*room1;
	t_room	*room2;

	room1 = getroom1(line, *map);
	room2 = getroom2(line, *map);
	linker(room1, room2);
}

void		setroom(char *line, t_room **room)
{
	t_room	*new;
	char	*name;
	t_point	coords;

	name = getroomname(line);
	coords = getcoords(line);
	new = roomnew(name, coords, NULL);
	add_room(room, new);
}
