/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_set_width.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 20:28:10 by aromny-w          #+#    #+#             */
/*   Updated: 2019/05/22 20:28:11 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_set_width(const char **format, va_list arg, t_pf *info)
{
	while (ft_isdigit(**format) || **format == '*')
	{
		info->width = 0;
		if (**format != '*')
			while (ft_isdigit(**format))
				info->width = 10 * info->width + (*(*format)++ - '0');
		else
		{
			if ((info->width = va_arg(arg, int)) < 0)
			{
				info->width *= -1;
				info->flags.minus = 1;
			}
			(*format)++;
		}
	}
}
