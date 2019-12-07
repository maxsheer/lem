/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_form_percent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 20:37:40 by aromny-w          #+#    #+#             */
/*   Updated: 2019/03/10 20:37:42 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print(t_pf *info, int len)
{
	if (info->width > 0 && !info->flags.minus)
		ft_padchar(!info->flags.zero ? ' ' : '0', info->width);
	ft_putchar('%');
	if (info->width > 0 && info->flags.minus)
		ft_padchar(' ', info->width);
	return (len + (info->width > 0 ? info->width : 0));
}

int			pf_form_percent(t_pf *info)
{
	int	len;

	len = 1;
	info->width--;
	return (print(info, len));
}
