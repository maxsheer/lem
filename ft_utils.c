/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlynesse <tlynesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 13:32:48 by tlynesse          #+#    #+#             */
/*   Updated: 2019/12/07 13:32:59 by tlynesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		link_di(t_room **src, t_room **dst)
{
	t_link	*tmp;

	tmp = (*src)->link;
	while (tmp)
	{
		if (tmp->room == *dst)
		{
			tmp->weight = INFINITY;
			break ;
		}
		tmp = tmp->next;
	}
	return (1);
}

int		double_link(t_room *room, char *name1, char *name2)
{
	t_link	*tmp;

	if (room)
	{
		while (ft_strcmp(name1, room->name))
			room = room->next;
		tmp = room->link;
		while (tmp)
		{
			if (!ft_strcmp(name2, tmp->room->name))
				return (1);
			tmp = tmp->next;
		}
	}
	return (0);
}

size_t	namelen(char *line)
{
	size_t	len;

	len = 0;
	while (ft_isalnum(*line) || *line == '_')
	{
		line++;
		len++;
	}
	return (len);
}

size_t	namelen1(char *line)
{
	size_t	len;

	len = 0;
	while (ft_isalnum(*line) || *line == '_')
	{
		line++;
		len++;
	}
	return (len);
}

size_t	namelen2(char *line)
{
	size_t	len;

	len = 0;
	while (*line && *line != '-')
		line++;
	if (!*line++)
		return (0);
	while (ft_isalnum(*line) || *line == '_')
	{
		line++;
		len++;
	}
	return (len);
}
