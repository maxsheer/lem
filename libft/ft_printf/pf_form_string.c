/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_form_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 19:53:16 by aromny-w          #+#    #+#             */
/*   Updated: 2019/03/02 19:53:17 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print(t_pf *info, char *str, int len)
{
	if (info->width > 0 && !info->flags.minus)
		ft_padchar(!info->flags.zero ? ' ' : '0', info->width);
	if ((info->spec != 'S' && !info->mods.l))
		ft_putnstr(str ? str : "(null)", info->prec);
	else
		ft_putnwcstr(str ? (wchar_t *)str : L"(null)", info->prec);
	if (info->width > 0 && info->flags.minus)
		ft_padchar(' ', info->width);
	return (len + (info->width > 0 ? info->width : 0));
}

int			pf_form_string(va_list arg, t_pf *info)
{
	char	*str;
	int		len;

	if (info->spec != 'S' && !info->mods.l)
	{
		str = va_arg(arg, char *);
		len = (int)ft_strnlen(str ? str : "(null)", info->prec);
	}
	else
	{
		str = (char *)va_arg(arg, wchar_t *);
		len = (int)ft_wcsnlen(str ? (wchar_t *)str : L"(null)", info->prec);
	}
	info->width -= len;
	return (print(info, str, len));
}
