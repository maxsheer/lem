/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_form_wcharacter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 20:47:09 by aromny-w          #+#    #+#             */
/*   Updated: 2019/03/25 20:47:11 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print(t_pf *info, wchar_t wc, int len)
{
	if (info->width > 0 && !info->flags.minus)
		ft_padchar(!info->flags.zero ? ' ' : '0', info->width);
	ft_putwchar(wc);
	if (info->width > 0 && info->flags.minus)
		ft_padchar(' ', info->width);
	return (len + (info->width > 0 ? info->width : 0));
}

int			pf_form_wcharacter(va_list arg, t_pf *info)
{
	wchar_t	wc;
	int		len;

	wc = va_arg(arg, wchar_t);
	if (wc < 128)
		len = 1;
	else if (wc < 2048)
		len = 2;
	else if (wc < 65536)
		len = 3;
	else
		len = 4;
	info->width -= len;
	return (print(info, wc, len));
}
