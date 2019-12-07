/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_set_prec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 21:09:12 by aromny-w          #+#    #+#             */
/*   Updated: 2019/05/24 21:09:15 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_set_prec(const char **format, va_list arg, t_pf *info)
{
	if (**format == '.')
	{
		info->prec = 0;
		(*format)++;
		if (**format != '*')
			while (ft_isdigit(**format))
				info->prec = 10 * info->prec + (*(*format)++ - '0');
		else
		{
			if ((info->prec = va_arg(arg, int)) < 0)
				info->prec = -1;
			(*format)++;
		}
	}
}
