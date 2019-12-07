/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlynesse <tlynesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 13:34:30 by tlynesse          #+#    #+#             */
/*   Updated: 2019/12/07 13:40:35 by tlynesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			linecount(int *len, int k, int ants)
{
	int	threshold;
	int	i;

	threshold = len[0];
	while (ants)
	{
		i = -1;
		while (ants && ++i < k)
		{
			if (len[i] == threshold)
			{
				len[i]++;
				ants--;
			}
		}
		threshold++;
	}
	return (len[0]);
}

int			brakingsystem(t_path *curr, t_path *prev, int k, int ants)
{
	int	i;
	int	len_curr[k];
	int	len_prev[k - 1];

	if (k == 1)
		return (1);
	i = -1;
	while (++i < k)
		len_curr[i] = curr[i].len / 2;
	i = -1;
	while (++i < k - 1)
		len_prev[i] = prev[i].len / 2;
	if (linecount(len_prev, k - 1, ants) < linecount(len_curr, k, ants))
	{
		free(curr);
		return (0);
	}
	return (1);
}

static void	lem_in(int fd)
{
	t_map	map;

	map_init(&map);
	parse_input(&map, fd, NULL);
	if (!val_data(map))
		map_delete(&map, NULL, 1);
	solver(map, map.end->links > map.ants ? map.ants : map.end->links);
}

int			main(int argc, char **argv)
{
	if (argc == 1)
		lem_in(0);
	else if (argc == 2)
		lem_in(open(argv[1], O_RDONLY));
	else
		exit_w(-1);
	exit_w(1);
}
