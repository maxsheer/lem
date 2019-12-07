/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_form_pointer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 19:54:41 by aromny-w          #+#    #+#             */
/*   Updated: 2019/03/02 19:54:43 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	puthexnbr(uintmax_t n, char a)
{
	if (n < 16)
		ft_putchar(n + (n < 10 ? '0' : a - 10));
	else
	{
		puthexnbr(n / 16, a);
		puthexnbr(n % 16, a);
	}
}

static int	nlen(uintmax_t n)
{
	int	len;

	len = 1;
	while (n /= 16)
		len++;
	return (len);
}

static int	print(t_pf *info, uintmax_t n, int len)
{
	if (info->width > 0 && !info->flags.minus && !info->flags.zero)
		ft_padchar(' ', info->width);
	ft_putstr(info->spec != 'X' ? "0x" : "0X");
	if (info->prec > 0)
		ft_padchar('0', info->prec);
	else if (info->width > 0 && !info->flags.minus && info->flags.zero)
		ft_padchar('0', info->width);
	if (!(!n && !info->prec))
		puthexnbr(n, info->spec != 'X' ? 'a' : 'A');
	if (info->width > 0 && info->flags.minus)
		ft_padchar(' ', info->width);
	return (len + (info->width > 0 ? info->width : 0));
}

int			pf_form_pointer(va_list arg, t_pf *info)
{
	uintmax_t	n;
	int			len;

	n = (uintmax_t)va_arg(arg, void *);
	if (!(!n && !info->prec))
	{
		len = nlen(n) > info->prec ? nlen(n) : info->prec;
		info->prec -= nlen(n);
	}
	else
		len = 0;
	len += 2;
	info->width -= len;
	return (print(info, n, len));
}
