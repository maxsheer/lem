/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlynesse <tlynesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 13:27:46 by tlynesse          #+#    #+#             */
/*   Updated: 2019/12/07 13:27:47 by tlynesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		val_data(t_map map)
{
	if (map.ants <= 0)
		return (0);
	if (!map.start || !map.end || !map.start->links || !map.end->links)
		return (0);
	return (1);
}

void	inp_err(t_map *map, int fd, char **line)
{
	close(fd);
	free(*line);
	map_delete(map, NULL, 1);
}

int		parse_command(t_map *map, int fd, char **line)
{
	char	cmd[ft_strlen(*line) + 1];

	ft_strcpy(cmd, *line);
	if (ft_strcmp("##start", cmd) && ft_strcmp("##end", cmd))
		return (0);
	ft_lstadd(&map->input, ft_lstnew(*line, ft_strlen(*line) + 1));
	free(*line);
	if (get_next_line(fd, line) != 1)
		*line = ft_strdup("");
	if (!isroom(*line, map->room))
		inp_err(map, fd, line);
	else if (!ft_strcmp("##start", cmd))
	{
		setroom(*line, &map->start);
		add_room(&map->room, map->start);
	}
	else if (!ft_strcmp("##end", cmd))
	{
		setroom(*line, &map->end);
		add_room(&map->room, map->end);
	}
	return (1);
}

void	parse_input(t_map *map, int fd, char *line)
{
	int		s[3];

	ft_memset(s, 0, sizeof(s));
	while (get_next_line(fd, &line) == 1)
	{
		if (isantnbr(line) && map->ants < 0 && !s[1] && !s[2] && (s[0] = 1))
			map->ants = ft_getnbr(line);
		else if (isroom(line, map->room) && s[0] && !s[2] && (s[1] = 1))
			setroom(line, &map->room);
		else if (islink(line, map->room) && s[0] && s[1] && (s[2] = 1))
			setlink(line, map);
		else if (iscomment(line))
			(void)line;
		else if (iscommand(line))
			parse_command(map, fd, &line) ? s[1] = 1 : 0;
		else
			inp_err(map, fd, &line);
		ft_lstadd(&map->input, ft_lstnew(line, ft_strlen(line) + 1));
		free(line);
	}
	rev_data(map);
	close(fd);
}
