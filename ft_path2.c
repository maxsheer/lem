/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlynesse <tlynesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 13:29:27 by tlynesse          #+#    #+#             */
/*   Updated: 2019/12/07 13:29:40 by tlynesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	add_path(t_path **path, t_path *new)
{
	new->next = *path;
	*path = new;
}

t_path	*new_path(t_way *way, size_t len)
{
	t_path	*path;

	if (!(path = (t_path *)malloc(sizeof(t_path))))
		exit_w(-1);
	path->way = way;
	path->len = len;
	path->limit = 0;
	return (path);
}

void	*free_ways(t_path *tmp, void *ret)
{
	t_way *tmp_ptr;

	tmp_ptr = tmp->way;
	if (tmp->way && tmp->way->next)
		tmp->way = tmp->way->next;
	free(tmp_ptr);
	tmp_ptr = NULL;
	return (ret);
}

void	best_path(t_path **new, t_path *tmp, t_map *map)
{
	t_way	*ptr;

	ft_memset(*new, 0, sizeof(new));
	ptr = tmp->way;
	while (ptr)
	{
		add_way(&(*new)->way, init_way(ptr->room));
		ptr = ptr->next;
	}
	(*new)->len = tmp->len;
	add_path(&map->buf, new_path((*new)->way, (*new)->len));
}
