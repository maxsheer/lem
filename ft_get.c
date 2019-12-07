/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlynesse <tlynesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 13:20:31 by tlynesse          #+#    #+#             */
/*   Updated: 2019/12/07 13:47:16 by tlynesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room	*getroom1(char *line, t_map map)
{
	char	*name;
	size_t	len;

	len = 0;
	while (line[len] != '-')
		len++;
	name = ft_strsub(line, 0, len);
	while (map.room && ft_strcmp(name, map.room->name))
		map.room = map.room->next;
	free(name);
	return (map.room);
}

t_room	*getroom2(char *line, t_map map)
{
	char	*name;

	while (*line != '-')
		line++;
	name = ft_strdup(++line);
	while (map.room && ft_strcmp(name, map.room->name))
		map.room = map.room->next;
	free(name);
	return (map.room);
}

t_point	getcoords(char *line)
{
	t_point	coords;

	while (*line != ' ')
		line++;
	coords.x = ft_getnbr(++line);
	while (*line != ' ')
		line++;
	coords.y = ft_getnbr(++line);
	return (coords);
}

char	*getroomname(char *line)
{
	size_t	len;

	len = 0;
	while (line[len] != ' ')
		len++;
	return (ft_strsub(line, 0, len));
}
