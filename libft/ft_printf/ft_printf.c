/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 17:02:32 by aromny-w          #+#    #+#             */
/*   Updated: 2019/05/28 13:10:18 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	convert(va_list arg, t_pf *info)
{
	if (info->spec == '%')
		return (pf_form_percent(info));
	if (info->spec == 'd' || info->spec == 'i' || info->spec == 'D')
		return (pf_form_integer(arg, info));
	if (info->spec == 'u' || info->spec == 'U')
		return (pf_form_unsigned(arg, info));
	if (info->spec == 'o' || info->spec == 'O')
		return (pf_form_octal(arg, info));
	if (info->spec == 'x' || info->spec == 'X')
		return (pf_form_hexa(arg, info));
	if (info->spec == 'f' || info->spec == 'F')
		return (pf_form_float(arg, info));
	if (info->spec == 'c')
		return (pf_form_character(arg, info));
	if (info->spec == 's' || info->spec == 'S')
		return (pf_form_string(arg, info));
	if (info->spec == 'p')
		return (pf_form_pointer(arg, info));
	if (info->spec == 'C')
		return (pf_form_wcharacter(arg, info));
	return (pf_form_unknown(info));
}

static int	isattribute(int c)
{
	if (c == '#' || c == '0' || c == '-' || c == ' ' || c == '+')
		return (1);
	if (ft_isdigit(c) || c == '*' || c == '.')
		return (1);
	if (c == 'h' || c == 'l' || c == 'j' || c == 't' || c == 'z' || c == 'q' ||
		c == 'L')
		return (1);
	return (0);
}

static int	parse(const char **format, va_list arg, t_pf *info)
{
	int		len;

	(*format)++;
	pf_initstruct(info);
	while (isattribute(**format))
	{
		pf_set_flags(format, &info->flags);
		pf_set_width(format, arg, info);
		pf_set_prec(format, arg, info);
		pf_set_mod(format, &info->mods);
	}
	pf_set_spec(format, info);
	if (!info->spec || (len = convert(arg, info)) == -1)
		return (-1);
	return (info->written += len);
}

static int	print(const char *format, va_list arg)
{
	t_pf	info;

	info.written = 0;
	while (*format)
	{
		if (*format != '%')
		{
			ft_putchar(*format);
			info.written++;
		}
		else if ((parse(&format, arg, &info)) == -1)
			return (info.written);
		format++;
	}
	return (info.written);
}

int			ft_printf(const char *format, ...)
{
	va_list	arg;
	int		done;

	va_start(arg, format);
	done = print(format, arg);
	va_end(arg);
	return (done);
}
