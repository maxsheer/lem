/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_form_float.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 18:16:28 by aromny-w          #+#    #+#             */
/*   Updated: 2019/03/22 18:16:29 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		putnbr(uintmax_t n)
{
	if (n < 10)
		ft_putchar(n + '0');
	else
	{
		putnbr(n / 10);
		putnbr(n % 10);
	}
}

static void		putfltnbr(t_pf *info, long double n)
{
	n = n < 0 ? -n : n;
	n += 5L / ft_powl(10L, info->prec + 1);
	putnbr(n);
	n -= (uintmax_t)n;
	if (info->prec || info->flags.hash)
	{
		ft_putchar('.');
		while (info->prec--)
		{
			ft_putchar((uintmax_t)(n *= 10L) + '0');
			n -= (uintmax_t)n;
		}
	}
}

static int		nlen(long long n)
{
	int	len;

	len = 1;
	while (n /= 10)
		len++;
	return (len);
}

static int		print(t_pf *info, long double n, int len)
{
	if (info->width > 0 && !info->flags.minus && (!info->flags.zero || n != n))
		ft_padchar(' ', info->width);
	if (n < 0)
		ft_putchar('-');
	else if (n == n && (info->flags.space || info->flags.plus))
		ft_putchar(info->flags.space ? ' ' : '+');
	if (n == n && info->width > 0 && !info->flags.minus && info->flags.zero)
		ft_padchar('0', info->width);
	if (n == n && n != n / 0)
		putfltnbr(info, n);
	else if (n != n)
		ft_putstr(info->spec != 'F' ? "nan" : "NAN");
	else if (n == n / 0)
		ft_putstr(info->spec != 'F' ? "inf" : "INF");
	if (info->width > 0 && info->flags.minus)
		ft_padchar(' ', info->width);
	return (len + (info->width > 0 ? info->width : 0));
}

int				pf_form_float(va_list arg, t_pf *info)
{
	long double	n;
	int			len;

	if (!info->mods.ll)
		n = va_arg(arg, double);
	else
		n = va_arg(arg, long double);
	if (n == n && n != n / 0)
		len = nlen(n) + (!info->prec ? 0 : info->prec + 1);
	else
		len = 3;
	if (n == n && (n < 0 || info->flags.plus || info->flags.space))
		len++;
	info->width -= len;
	return (print(info, n, len));
}
