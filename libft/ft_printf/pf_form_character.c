/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_form_character.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wclayton <wclayton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 19:30:13 by wclayton          #+#    #+#             */
/*   Updated: 2019/12/07 14:18:35 by wclayton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print(t_pf *info, int c, int len)
{
	if (info->width > 0 && !info->flags.minus)
		ft_padchar(!info->flags.zero ? ' ' : '0', info->width);
	ft_putchar(c);
	if (info->width > 0 && info->flags.minus)
		ft_padchar(' ', info->width);
	return (len + (info->width > 0 ? info->width : 0));
}

int			pf_form_character(va_list arg, t_pf *info)
{
	int		c;
	int		len;

	if (info->mods.l)
		return (pf_form_wcharacter(arg, info));
	c = va_arg(arg, int);
	len = 1;
	info->width--;
	return (print(info, c, len));
}
