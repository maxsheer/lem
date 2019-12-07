/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlynesse <tlynesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 13:17:24 by tlynesse          #+#    #+#             */
/*   Updated: 2019/12/07 13:17:45 by tlynesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	check_overlap(t_path new)
{
	t_way	*tmp;
	int		check;

	check = 0;
	tmp = new.way;
	while (tmp && tmp->next)
	{
		if (tmp->room->name != tmp->next->room->name)
			if (tmp->room->in == 1 && tmp->next->room->out == 1)
				check = link_di(&tmp->next->room, &tmp->room);
		if (tmp->room->name == tmp->next->room->name)
			if (tmp->room->out == 1 && tmp->next->room->in == 1)
				check = link_di(&tmp->next->room, &tmp->room);
		tmp = tmp->next;
	}
	return (check);
}

int	isexist(t_room *room, char *name)
{
	while (room && ft_strcmp(name, room->name))
		room = room->next;
	if (room)
		return (1);
	return (0);
}

int	islink(char *line, t_room *room)
{
	char	name1[1 + namelen1(line)];
	char	name2[1 + namelen2(line)];
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (ft_isalnum(*line) || *line == '_')
		name1[i++] = *line++;
	name1[i] = '\0';
	if (*line++ != '-')
		return (0);
	if (*line == 'L' || *line == '#')
		return (0);
	while (ft_isalnum(*line) || *line == '_')
		name2[j++] = *line++;
	name2[j] = '\0';
	if (!isexist((room), name1) || !isexist(room, name2))
		return (0);
	if (double_link(room, name1, name2))
		return (0);
	if (!*line)
		return (1);
	return (0);
}

int	isname(char **line, t_room *room)
{
	char	name[1 + namelen(*line)];
	size_t	i;

	i = 0;
	while (ft_isalnum(**line) || **line == '_')
		name[i++] = *(*line)++;
	name[i] = '\0';
	while (room && ft_strcmp(name, room->name))
		room = room->next;
	if (*(*line)++ == ' ' && !room)
		return (1);
	return (0);
}

int	isroom(char *line, t_room *room)
{
	if (*line == 'L' || *line == '#')
		return (0);
	if (!isname(&line, room))
		return (0);
	if (!iscoord1(&line))
		return (0);
	if (!iscoord2(&line))
		return (0);
	return (1);
}
