/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_form_integer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 19:41:51 by aromny-w          #+#    #+#             */
/*   Updated: 2019/03/02 19:41:52 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		putunbr(uintmax_t n)
{
	if (n < 10)
		ft_putchar(n + '0');
	else
	{
		putunbr(n / 10);
		putunbr(n % 10);
	}
}

static int		nlen(intmax_t n)
{
	int	len;

	len = 1;
	while (n /= 10)
		len++;
	return (len);
}

static int		print(t_pf *info, intmax_t n, int len)
{
	if (info->width > 0 && !info->flags.minus && !info->flags.zero)
		ft_padchar(' ', info->width);
	if (n < 0)
		ft_putchar('-');
	else if (info->flags.space || info->flags.plus)
		ft_putchar(info->flags.space ? ' ' : '+');
	if (info->prec > 0)
		ft_padchar('0', info->prec);
	else if (info->width > 0 && !info->flags.minus && info->flags.zero)
		ft_padchar('0', info->width);
	if (len)
		putunbr(n < 0 ? -n : n);
	if (info->width > 0 && info->flags.minus)
		ft_padchar(' ', info->width);
	return (len + (info->width > 0 ? info->width : 0));
}

static intmax_t	cast(intmax_t n, t_mods mods, char spec)
{
	if (spec == 'D')
		return ((long)n);
	else if (mods.q)
		return ((quad_t)n);
	else if (mods.z)
		return ((size_t)n);
	else if (mods.t)
		return ((ptrdiff_t)n);
	else if (mods.j)
		return ((intmax_t)n);
	else if (mods.ll)
		return ((long long)n);
	else if (mods.l)
		return ((long)n);
	else if (mods.h)
		return ((short)n);
	else if (mods.hh)
		return ((signed char)n);
	return ((int)n);
}

int				pf_form_integer(va_list arg, t_pf *info)
{
	intmax_t	n;
	int			len;

	n = cast(va_arg(arg, intmax_t), info->mods, info->spec);
	len = 0;
	if (!(!n && !info->prec))
	{
		if ((len = nlen(n)) < info->prec)
			len = info->prec;
		if (n < 0 || info->flags.plus || info->flags.space)
			len++;
		info->width -= len;
		info->prec -= nlen(n);
	}
	else
		info->width -= info->flags.space;
	return (print(info, n, len));
}
