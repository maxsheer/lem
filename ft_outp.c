/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_outp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlynesse <tlynesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 13:27:53 by tlynesse          #+#    #+#             */
/*   Updated: 2019/12/07 13:28:08 by tlynesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		printants(t_ant *ant, int n)
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

void	writeinput(t_list *input)
{
	while (input)
	{
		ft_putendl(input->content);
		input = input->next;
	}
	ft_putchar('\n');
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
