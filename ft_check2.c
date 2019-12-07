/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlynesse <tlynesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 13:17:59 by tlynesse          #+#    #+#             */
/*   Updated: 2019/12/07 13:18:00 by tlynesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

int	iscoord2(char **line)
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

int	iscoord1(char **line)
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
