/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rev.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlynesse <tlynesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 13:29:47 by tlynesse          #+#    #+#             */
/*   Updated: 2019/12/07 13:30:02 by tlynesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	rev_link1(t_link **link)
{
	t_link	*prev;
	t_link	*curr;
	t_link	*next;

	prev = NULL;
	curr = *link;
	while (curr)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	*link = prev;
}

void	rev_room(t_room **room)
{
	t_room	*prev;
	t_room	*curr;
	t_room	*next;

	prev = NULL;
	curr = *room;
	while (curr)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	*room = prev;
}

void	rev_link(t_room **room1, t_room **room2)
{
	t_link	*link1;
	t_link	*link2;

	link1 = (*room1)->link;
	link2 = (*room2)->link;
	while (link1->room != *room2)
		link1 = link1->next;
	if ((*room1)->name == (*room2)->name)
		link1->weight = link1->weight == 0 ? INFINITY : 0;
	else
		link1->weight = link1->weight == 1 ? INFINITY : 1;
	while (link2->room != *room1)
		link2 = link2->next;
	if ((*room1)->name == (*room2)->name)
		link2->weight = link2->weight == INFINITY ? 0 : INFINITY;
	else
		link2->weight = link2->weight == INFINITY ? 1 : INFINITY;
}

void	rev_paths(t_path *init, t_path new, size_t k)
{
	t_way	*tmp;
	size_t	i;

	i = -1;
	if (!init)
		return ;
	while (++i < k)
	{
		tmp = init[i].way;
		while (tmp && tmp->next && tmp != new.way)
		{
			rev_link(&tmp->room, &tmp->next->room);
			tmp = tmp->next;
		}
	}
}

void	rev_data(t_map *map)
{
	t_room	*tmp;

	rev_room(&map->room);
	tmp = map->room;
	while (tmp)
	{
		rev_link1(&tmp->link);
		tmp = tmp->next;
	}
	ft_lstrev(&map->input);
}
