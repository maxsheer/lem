/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_form_hexa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 19:44:55 by aromny-w          #+#    #+#             */
/*   Updated: 2019/03/02 19:44:56 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void			puthexnbr(uintmax_t n, char a)
{
	if (n < 16)
		ft_putchar(n + (n < 10 ? '0' : a - 10));
	else
	{
		puthexnbr(n / 16, a);
		puthexnbr(n % 16, a);
	}
}

static int			nlen(uintmax_t n)
{
	int	len;

	len = 1;
	while (n /= 16)
		len++;
	return (len);
}

static int			print(t_pf *info, uintmax_t n, int len)
{
	if (info->width > 0 && !info->flags.minus && !info->flags.zero)
		ft_padchar(' ', info->width);
	if (n && info->flags.hash)
		ft_putstr(info->spec != 'X' ? "0x" : "0X");
	if (info->prec > 0)
		ft_padchar('0', info->prec);
	else if (info->width > 0 && !info->flags.minus && info->flags.zero)
		ft_padchar('0', info->width);
	if (len)
		puthexnbr(n, info->spec != 'X' ? 'a' : 'A');
	if (info->width > 0 && info->flags.minus)
		ft_padchar(' ', info->width);
	return (len + (info->width > 0 ? info->width : 0));
}

static uintmax_t	cast(uintmax_t n, t_mods mods)
{
	if (mods.q)
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

int					pf_form_hexa(va_list arg, t_pf *info)
{
	uintmax_t	n;
	int			len;

	n = cast(va_arg(arg, uintmax_t), info->mods);
	len = 0;
	if (!(!n && !info->prec))
	{
		len = nlen(n) > info->prec ? nlen(n) : info->prec;
		if (n > 0 && info->flags.hash)
			len += 2;
		info->width -= len;
		info->prec -= nlen(n);
	}
	return (print(info, n, len));
}
