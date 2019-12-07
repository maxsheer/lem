#include "lem_in.h"

static void	rooml_comp(t_link **link, t_room *end)
{
	t_link	*tmp;
	t_link	*new;
	t_link	*del;

	new = NULL;
	tmp = *link;
	if (tmp->room->in)
		add_link(&new, init_link(tmp->room->link->room, INFINITY));
	while (tmp->next)
	{
		if (tmp->next->room->in || tmp->next->room == end)
		{
			del = tmp->next;
			if (tmp->next->room->in)
				add_link(&new, init_link(tmp->next->room->link->room, INFINITY));
			tmp->next = tmp->next->next;
			free(del);
		}
		else
			tmp = tmp->next;
	}
	rev_link1(&new);
	tmp->next = new;
}

static void	el_comp(t_link **link, t_room *start)
{
	t_link	*tmp;
	t_link	*new;

	new = NULL;
	tmp = *link;
	if (tmp->room->in)
		add_link(&new, init_link(tmp->room->link->room, INFINITY));
	else if (tmp->room == start)
		add_link(&new, init_link(tmp->room, INFINITY));
	while (tmp->next)
	{
		if (tmp->next->room->in)
			add_link(&new, init_link(tmp->next->room->link->room, INFINITY));
		else if (tmp->next->room == start)
			add_link(&new, init_link(tmp->next->room, INFINITY));
		tmp = tmp->next;
	}
	rev_link1(&new);
	del_link(link);
	*link = new;
}

static void	sl_comp(t_link **link)
{
	return ((void)link);
}

void		link_comp(t_room **room, t_room *start, t_room *end)
{
	t_room	*tmp;

	tmp = *room;
	while (tmp)
	{
		if (tmp->link && tmp == start)
			sl_comp(&tmp->link);
		else if (tmp->link && tmp == end)
			el_comp(&tmp->link, start);
		else if (tmp->in && tmp->link)
			rooml_comp(&tmp->link, end);
		tmp = tmp->next;
	}
}

static int	printants(t_ant *ant, int n)
{
	int	i;
	int	check;

	check = 0;
	i = -1;
	while (++i < n)
	{
		if (ant[i].way)
		{
			if (check)
				ft_printf(" ");
			check++;
			ft_printf("L%d-%s", ant[i].number, ant[i].way->room->name);
			if (!ant[i].way->next)
				ant[i].way = ant[i].way->next;
			else
				ant[i].way = ant[i].way->next->next;
		}
	}
	if (!check)
		return (0);
	ft_printf("\n");
	return (1);
}

static void	set_truelen(t_path *path, int k)
{
	int	i;

	i = -1;
	while (++i < k)
		path[i].len = path[i].len / 2;
}

static void	set_limits(t_path *path, int k, int ants)
{
	int	i;
	int	threshold;

	threshold = path[0].len;
	while (ants)
	{
		i = -1;
		while (ants && ++i < k)
		{
			if (path[i].len + path[i].limit == threshold)
			{
				path[i].limit++;
				ants--;
			}
		}
		threshold++;
	}
}

void		antsdist(t_path *path, int k, int ants)
{
	t_ant	ant[ants];
	int		lines;
	int		i;
	int		n;

	ft_memset(ant, 0, sizeof(ant));
	set_truelen(path, k);
	set_limits(path, k, ants);
	n = 0;
	lines = path[0].len + path[0].limit;
	while (ants)
	{
		i = -1;
		while (++i < k)
		{
			if (path[i].limit && n < ants)
			{
				ant[n].number = n + 1;
				ant[n++].way = path[i].way->next;
				path[i].limit--;
			}
		}
		if (!printants(ant, ants))
			break ;
	}
}

static void	shiftpaths(t_path *path, size_t k)
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

static int	isinvalid(t_way *way)
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

void		dis_paths(t_path *path, size_t k)
{
	size_t	i;

	i = -1;
	while (++i < k)
		if (path[i].way && isinvalid(path[i].way))
			ft_memset(&path[i], 0, sizeof(path[i]));
	shiftpaths(path, k);
}

static int	link_di(t_room **src, t_room **dst)
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

int			check_overlap(t_path new)
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

static int		double_link(t_room *room, char *name1, char *name2)
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

static int		isexist(t_room *room, char *name)
{
	while (room && ft_strcmp(name, room->name))
		room = room->next;
	if (room)
		return (1);
	return (0);
}

static size_t	namelen2(char *line)
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

static size_t	namelen1(char *line)
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

int				islink(char *line, t_room *room)
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

void	add_way(t_way **way, t_way *new)
{
	new->next = *way;
	*way = new;
}

t_way	*init_way(t_room *room)
{
	t_way	*way;

	if (!(way = (t_way *)malloc(sizeof(t_way))))
		exit_w(-1);
	way->room = room;
	way->next = NULL;
	return (way);
}

void		*free_ways(t_path *tmp, void *ret)
{
	t_way *tmp_ptr;

	tmp_ptr = tmp->way;
	if (tmp->way && tmp->way->next)
		tmp->way = tmp->way->next;
	free(tmp_ptr);
	tmp_ptr = NULL;
	return (ret);
}

void		best_path(t_path **new, t_path *tmp, t_map *map)
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

void		*depth_search(t_map *map, t_path *new, t_path tmp, t_room *room)
{
	t_link	*link;

	add_way(&tmp.way, init_way(room));
	tmp.len++;
	if (tmp.len > map->depth || !room || (new->way && new->len < tmp.len) ||
		tmp.len > room->dist)
		return (free_ways(&tmp, NULL));
	else if (tmp.way->room == map->end && (!new->way || tmp.len < new->len))
	{
		room->dist = tmp.len;
		best_path(&new, &tmp, map);
		return (free_ways(&tmp, NULL));
	}
	room->dist = tmp.len;
	link = tmp.way->room->link;
	while (link)
	{
		if (link->weight != INFINITY)
			depth_search(map, new, tmp, link->room);
		link = link->next;
	}
	return (free_ways(&tmp, NULL));
}

int	isantnbr(char *line)
{
	long	nbr;

	nbr = 0;
	if (!ft_isdigit(*line) && *line != '+')
		return (0);
	if (*line == '+')
		line++;
	while (ft_isdigit(*line) && nbr <= INT_MAX)
		nbr = 10 * nbr + (*line++ - '0');
	if (!*line && nbr <= INT_MAX)
		return (1);
	return (0);
}

int	iscommand(char *line)
{
	if (*line == '#' && *(line + 1) == '#')
		return (1);
	return (0);
}

int	iscomment(char *line)
{
	if (*line == '#' && *(line + 1) != '#')
		return (1);
	return (0);
}

static int		iscoord2(char **line)
{
	long	nbr;

	nbr = 0;
	while (ft_isspace(**line))
		(*line)++;
	if (**line == '-')
		return (0);
	if (ft_isdigit(**line))
		while (ft_isdigit(**line) && nbr <= INT_MAX)
			nbr = 10 * nbr + (*(*line)++ - '0');
	else
		return (0);
	if (**line == '\0' && nbr <= INT_MAX)
		return (1);
	return (0);
}

static int		iscoord1(char **line)
{
	long	nbr;

	nbr = 0;
	while (ft_isspace(**line))
		(*line)++;
	if (**line == '-')
		return (0);
	if (ft_isdigit(**line))
		while (ft_isdigit(**line) && nbr <= INT_MAX)
			nbr = 10 * nbr + (*(*line)++ - '0');
	else
		return (0);
	if (*(*line)++ == ' ' && nbr <= INT_MAX)
		return (1);
	return (0);
}

static size_t	namelen(char *line)
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

static int		isname(char **line, t_room *room)
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

int				isroom(char *line, t_room *room)
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

void	add_link(t_link **link, t_link *new)
{
	new->next = *link;
	*link = new;
}

t_link	*init_link(t_room *room, float weight)
{
	t_link *link;

	if (!(link = (t_link *)malloc(sizeof(t_link))))
		exit_w(-1);
	link->room = room;
	link->weight = weight;
	link->next = NULL;
	return (link);
}

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

void	add_room(t_room **room, t_room *new)
{
	new->next = *room;
	*room = new;
}

t_room		*roomnew(char *name, t_point coords, t_link *link)
{
	t_room	*room;

	if (!(room = (t_room *)malloc(sizeof(t_room))))
		exit_w(-1);
	room->name = name;
	room->coords = coords;
	room->dist = INFINITY;
	room->in = 0;
	room->out = 0;
	room->links = 0;
	room->link = link;
	room->next = NULL;
	return (room);
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

static void		linker(t_room *room_1, t_room *room_2)
{
	add_link(&room_1->link, init_link(room_2, 1));
	add_link(&room_2->link, init_link(room_1, 1));
	room_1->links++;
	room_2->links++;
}

static t_room	*getroom2(char *line, t_map map)
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

static t_room	*getroom1(char *line, t_map map)
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

void			setlink(char *line, t_map *map)
{
	t_room	*room1;
	t_room	*room2;

	room1 = getroom1(line, *map);
	room2 = getroom2(line, *map);
	linker(room1, room2);
}

static t_point	getcoords(char *line)
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

static char		*getroomname(char *line)
{
	size_t	len;

	len = 0;
	while (line[len] != ' ')
		len++;
	return (ft_strsub(line, 0, len));
}

void			setroom(char *line, t_room **room)
{
	t_room	*new;
	char	*name;
	t_point	coords;

	name = getroomname(line);
	coords = getcoords(line);
	new = roomnew(name, coords, NULL);
	add_room(room, new);
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

static t_room	*getroomout(t_room *room)
{
	t_room	*out;
	t_link	*tmp;

	out = roomnew(room->name, room->coords, NULL);
	out->out = 1;
	tmp = room->link;
	while ((tmp))
	{
		add_link(&out->link, init_link(tmp->room, 1));
		tmp = tmp->next;
	}
	rev_link1(&out->link);
	return (out);
}

static t_room	*getroomin(t_room *room)
{
	t_room	*in;
	t_link	*tmp;

	in = room;
	in->in = 1;
	in->links = 1;
	tmp = in->link;
	while (tmp)
	{
		tmp->weight = INFINITY;
		tmp = tmp->next;
	}
	return (in);
}

static t_room	*getsplitroom(t_room *room)
{
	t_room	*in;
	t_room	*out;

	in = getroomin(room);
	out = getroomout(room);
	add_link(&in->link, init_link(out, 0));
	add_link(&out->link, init_link(in, INFINITY));
	out->next = in->next;
	in->next = out;
	return (in);
}

void			splitrooms(t_room **room, t_room *start, t_room *end)
{
	t_room	*tmp;

	tmp = *room;
	while (tmp)
	{
		if (tmp != start && tmp != end)
		{
			tmp = getsplitroom(tmp);
			tmp = tmp->next->next;
		}
		else
			tmp = tmp->next;
	}
	link_comp(room, start, end);
}

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

static void		height_init(t_room **room)
{
	t_room	*tmp;

	tmp = *room;
	while (tmp)
	{
		tmp->dist = INFINITY;
		tmp = tmp->next;
	}
}

static size_t	path_add(t_path *path, t_path new, size_t k)
{
	size_t	i;

	i = 0;
	if (path)
		while (i < k - 1 && path[i].way)
			i++;
	path[i].way = new.way;
	path[i].len = new.len;
	path_sort(path, k);
	return (++i);
}

static void		rev_link(t_room **room1, t_room **room2)
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

static void		rev_paths(t_path *init, t_path new, size_t k)
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

t_path			*path_finder(t_map *map, t_path *path, size_t k)
{
	t_path	new;

	ft_memset(&new, 0, sizeof(t_path));
	height_init(&map->room);
	rev_paths(path, new, k - 1);
	depth_search(map, &new, new, map->start);
	rev_paths(path, new, k - 1);
	if (!new.way)
		return (NULL);
	if (check_overlap(new))
	{
		dis_paths(path, k);
		return (path_finder(map, path, k));
	}
	else if (path_add(path, new, k) < k)
		return (path_finder(map, path, k));
	return (path);
}

static t_path	*tryagain(t_map *map, t_path *init, size_t k)
{
	map->depth = INFINITY;
	return (path_eval(map, init, k));
}

t_path			*path_eval(t_map *map, t_path *init, size_t k)
{
	t_path	*path;
	size_t	i;

	i = -1;
	if (!(path = (t_path *)malloc(sizeof(t_path) * k)))
		exit_w(-1);
	while (++i < k - 1 && init)
	{
		path[i].way = init[i].way;
		path[i].len = init[i].len;
		path[i].limit = init[i].limit;
	}
	ft_memset(&path[i], 0, sizeof(path[i]));
	if (!path_finder(map, path, k))
	{
		free(path);
		if (k == 1 && map->depth != INFINITY)
			return (tryagain(map, init, k));
		return (NULL);
	}
	return (path);
}

void	exit_w(int status)
{
	if (status == -1)
		ft_putstr_fd("ERROR\n", 2);
	if (status != -1)
		exit(EXIT_SUCCESS);
	else
		exit(EXIT_FAILURE);
}

static void	writeinput(t_list *input)
{
	while (input)
	{
		ft_putendl(input->content);
		input = input->next;
	}
	ft_putchar('\n');
}

static int		linecount(int *len, int k, int ants)
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

static int		brakingsystem(t_path *curr, t_path *prev, int k, int ants)
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

void			solver(t_map map, size_t max)
{
	t_path	*path[1 + max];
	size_t	k;

	k = 0;
	path[k] = NULL;
	splitrooms(&map.room, map.start, map.end);
	while (++k <= max)
	{
		if (!(path[k] = path_eval(&map, path[k - 1], k)) ||
		!brakingsystem(path[k], path[k - 1], k, map.ants))
			break ;
	}
	if (k != 1)
	{
		writeinput(map.input);
		antsdist(path[k - 1], k - 1, map.ants);
	}
	map_delete(&map, path, k);
}

static void	inp_err(t_map *map, int fd, char **line)
{
	close(fd);
	free(*line);
	map_delete(map, NULL, 1);
}

static void	rev_data(t_map *map)
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

int			parse_command(t_map *map, int fd, char **line)
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

void		parse_input(t_map *map, int fd, char *line)
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

void	del_link(t_link **link)
{
	t_link	*tmp;
	t_link	*next;

	tmp = *link;
	while (tmp)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	*link = NULL;
}

void	map_init(t_map *map)
{
	map->ants = -1;
	map->room = NULL;
	map->start = NULL;
	map->end = NULL;
	map->input = NULL;
	map->buf = NULL;
	map->depth = 200;
}

static void	del(void *elem, size_t size)
{
	size = 0;
	free(elem);
}

static void	del_rooms(t_room **room)
{
	t_room	*tmp;
	t_room	*next;

	tmp = *room;
	while (tmp)
	{
		next = tmp->next;
		del_link(&tmp->link);
		if (tmp->in == 0)
			free(tmp->name);
		free(tmp);
		tmp = next;
	}
	*room = NULL;
}

void		map_delete(t_map *map, t_path **path, int k)
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

static int		val_data(t_map map)
{
	if (map.ants <= 0)
		return (0);
	if (!map.start || !map.end || !map.start->links || !map.end->links)
		return (0);
	return (1);
}

void			lem_in(int fd)
{
	t_map	map;

	map_init(&map);
	parse_input(&map, fd, NULL);
	if (!val_data(map))
		map_delete(&map, NULL, 1);
	solver(map, map.end->links > map.ants ? map.ants : map.end->links);
}

int				main(int argc, char **argv)
{
	if (argc == 1)
		lem_in(0);
	else if (argc == 2)
		lem_in(open(argv[1], O_RDONLY));
	else
		exit_w(-1);
	exit_w(1);
}