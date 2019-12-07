/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wclayton <wclayton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 20:25:26 by wclayton          #+#    #+#             */
/*   Updated: 2019/12/07 14:21:42 by wclayton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <math.h>

typedef struct s_room	t_room;

typedef struct	s_way
{
	t_room			*room;
	struct s_way	*next;
}				t_way;

typedef struct	s_ant
{
	int		number;
	t_way	*way;
}				t_ant;

typedef struct	s_path
{
	t_way			*way;
	int				limit;
	int				len;
	struct s_path	*next;
}				t_path;

typedef struct	s_link
{
	t_room			*room;
	float			weight;
	struct s_link	*next;
}				t_link;

typedef struct	s_point
{
	int	x;
	int	y;
}				t_point;

struct			s_room
{
	char			*name;
	t_point			coords;
	float			dist;
	int				in;
	int				out;
	int				links;
	t_link			*link;
	struct s_room	*next;
};

typedef struct	s_map
{
	int				ants;
	t_room			*room;
	t_room			*start;
	t_room			*end;
	t_list			*input;
	t_path			*buf;
	float			depth;
}				t_map;

void			map_init(t_map *map);
void			parse_input(t_map *map, int fd, char *line);
void			setroom(char *line, t_room **room);
void			setlink(char *line, t_map *map);
void			solver(t_map map, size_t max);
void			splitrooms(t_room **room, t_room *start, t_room *end);
void			link_comp(t_room **room, t_room *start, t_room *end);
t_path			*path_eval(t_map *map, t_path *init, size_t k);
t_path			*path_finder(t_map *map, t_path *path, size_t k);
void			*depth_search(t_map *map, t_path *new, t_path tmp, \
t_room *room);
void			exit_w(int status);
void			map_delete(t_map *map, t_path **path, int k);
t_room			*roomnew(char *name, t_point coords, t_link *link);
void			add_room(t_room **room, t_room *new);
void			rev_room(t_room **room);
t_link			*init_link(t_room *room, float weight);
void			add_link(t_link **link, t_link *new);
void			rev_link1(t_link **link);
void			del_link(t_link **link);
t_way			*init_way(t_room *room);
void			add_way(t_way **way, t_way *new);
void			map_deleteway(t_way **way);
void			rev_way(t_way **way);
t_way			*waymap(t_way *way);
t_path			*new_path(t_way *way, size_t len);
void			map_deletepath(t_path **path);
void			add_path(t_path **path, t_path *new);
int				isantnbr(char *line);
int				isroom(char *line, t_room *room);
int				islink(char *line, t_room *room);
int				iscommand(char *line);
int				iscomment(char *line);
void			printstatus(t_path *path, int k);
void			printrooms(t_room *room);
int				check_overlap(t_path new);
void			dis_paths(t_path *path, size_t k);
void			path_sort(t_path *path, size_t k);
void			antsdist(t_path *path, int k, int ants);
t_point			getcoords(char *line);
int				val_data(t_map map);
int				printants(t_ant *ant, int n);
t_room			*getroom1(char *line, t_map map);
t_room			*getroom2(char *line, t_map map);
char			*getroomname(char *line);
void			linker(t_room *room_1, t_room *room_2);
void			rev_data(t_map *map);
void			del_rooms(t_room **room);
void			*free_ways(t_path *tmp, void *ret);
void			best_path(t_path **new, t_path *tmp, t_map *map);
void			height_init(t_room **room);
void			rev_paths(t_path *init, t_path new, size_t k);
size_t			path_add(t_path *path, t_path new, size_t k);
void			writeinput(t_list *input);
int				link_di(t_room **src, t_room **dst);
size_t			namelen(char *line);
size_t			namelen1(char *line);
size_t			namelen2(char *line);
int				double_link(t_room *room, char *name1, char *name2);
int				iscoord1(char **line);
int				iscoord2(char **line);

#endif
