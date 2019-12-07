/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlynesse <tlynesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 13:19:07 by tlynesse          #+#    #+#             */
/*   Updated: 2019/12/07 13:19:34 by tlynesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	map_deleteway(t_way **way)
{
	t_way	*tmp;
	t_way	*next;

	tmp = *way;
	while (tmp)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	*way = NULL;
}

void	map_deletepath(t_path **path)
{
	t_path	*tmp;
	t_path	*next;

	tmp = *path;
	while (tmp)
	{
		next = tmp->next;
		map_deleteway(&tmp->way);
		free(tmp);
		tmp = next;
	}
	*path = NULL;
}

void	del(void *elem, size_t size)
{
	size = 0;
	free(elem);
}

void	map_delete(t_map *map, t_path **path, int k)
{
	int	i;

	i = k;
	while (--i)
		free(path[i]);
	ft_lstdel(&map->input, del);
	map_deletepath(&map->buf);
	del_rooms(&map->room);
	if (k == 1)
		exit_w(-1);
}
