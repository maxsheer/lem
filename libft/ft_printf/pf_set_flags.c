/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_set_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 19:47:39 by aromny-w          #+#    #+#             */
/*   Updated: 2019/05/22 19:47:41 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	isflag(char c)
{
	if (c == '#' || c == '0' || c == '-' || c == ' ' || c == '+')
		return (1);
	return (0);
}

void		pf_set_flags(const char **format, t_flags *flags)
{
	while (isflag(**format))
	{
		if (**format == '#')
			flags->hash = 1;
		else if (**format == '0')
			flags->zero = 1;
		else if (**format == '-')
			flags->minus = 1;
		else if (**format == ' ')
			flags->space = 1;
		else if (**format == '+')
			flags->plus = 1;
		(*format)++;
	}
}
