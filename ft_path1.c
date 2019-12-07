/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlynesse <tlynesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 13:29:00 by tlynesse          #+#    #+#             */
/*   Updated: 2019/12/07 13:29:16 by tlynesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	shiftpaths(t_path *path, size_t k)
{
	size_t	i;
	size_t	j;

	i = -1;
	j = -1;
	while (++i < k)
		if (path[i].way)
			path[++j] = path[i];
	while (++j < k)
		ft_memset(&path[j], 0, sizeof(t_path));
}

int		isinvalid(t_way *way)
{
	t_way	*tmp;
	t_link	*link;

	tmp = way;
	while (tmp && tmp->next)
	{
		link = tmp->room->link;
		while (link->room != tmp->next->room)
			link = link->next;
		if (link->weight == INFINITY)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	dis_paths(t_path *path, size_t k)
{
	size_t	i;

	i = -1;
	while (++i < k)
		if (path[i].way && isinvalid(path[i].way))
			ft_memset(&path[i], 0, sizeof(path[i]));
	shiftpaths(path, k);
}

void	pathswap(t_path *a, t_path *b)
{
	t_path	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	path_sort(t_path *path, size_t k)
{
	size_t	i;

	i = 0;
	while (i + 1 < k && path[i].way && path[i + 1].way)
	{
		if (path[i].len > path[i + 1].len)
		{
			pathswap(&path[i], &path[i + 1]);
			i = 0;
		}
		i++;
	}
}
