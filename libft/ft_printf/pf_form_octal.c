/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_form_octal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 19:42:43 by aromny-w          #+#    #+#             */
/*   Updated: 2019/03/02 19:42:44 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void			putoctnbr(uintmax_t n)
{
	if (n < 8)
		ft_putchar(n + '0');
	else
	{
		putoctnbr(n / 8);
		putoctnbr(n % 8);
	}
}

static int			nlen(uintmax_t n, int hash)
{
	int	len;

	len = !(n > 0 && hash) ? 1 : 2;
	while (n /= 8)
		len++;
	return (len);
}

static int			print(t_pf *info, uintmax_t n, int len)
{
	if (info->width > 0 && !info->flags.minus)
		ft_padchar(!info->flags.zero ? ' ' : '0', info->width);
	if (info->prec > 0 || (n > 0 && info->flags.hash))
		ft_padchar('0', info->prec > 0 ? info->prec : 1);
	if (len && !(!n && !(len - info->prec)))
		putoctnbr(n);
	if (info->width > 0 && info->flags.minus)
		ft_padchar(' ', info->width);
	return (len + (info->width > 0 ? info->width : 0));
}

static uintmax_t	cast(uintmax_t n, t_mods mods, char spec)
{
	if (spec == 'O')
		return ((unsigned long)n);
	else if (mods.q)
		return ((u_quad_t)n);
	else if (mods.z)
		return ((size_t)n);
	else if (mods.t)
		return ((ptrdiff_t)n);
	else if (mods.j)
		return ((uintmax_t)n);
	else if (mods.ll)
		return ((unsigned long long)n);
	else if (mods.l)
		return ((unsigned long)n);
	else if (mods.h)
		return ((unsigned short)n);
	else if (mods.hh)
		return ((unsigned char)n);
	return ((unsigned int)n);
}

int					pf_form_octal(va_list arg, t_pf *info)
{
	uintmax_t	n;
	int			len;

	n = cast(va_arg(arg, uintmax_t), info->mods, info->spec);
	len = 0;
	if (!(!n && !info->prec))
	{
		len = nlen(n, info->flags.hash) > info->prec ?
		nlen(n, info->flags.hash) : info->prec;
		info->width -= len;
		info->prec -= nlen(n, 0);
	}
	else
	{
		len += info->prec += info->flags.hash;
		info->width -= info->flags.hash + info->flags.space;
	}
	return (print(info, n, len));
}
