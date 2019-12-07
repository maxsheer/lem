/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putwchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 20:20:16 by aromny-w          #+#    #+#             */
/*   Updated: 2019/06/21 20:20:17 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putwchar(wchar_t wc)
{
	if (wc <= 0x7F)
		ft_putchar(wc);
	else if (wc <= 0x7FF)
	{
		ft_putchar((wc >> 6) | 0xC0);
		ft_putchar((wc & 0x3F) | 0x80);
	}
	else if (wc <= 0xFFFF)
	{
		ft_putchar((wc >> 12) | 0xE0);
		ft_putchar(((wc >> 6) & 0x3F) | 0x80);
		ft_putchar((wc & 0x3F) | 0x80);
	}
	else if (wc <= 0x10FFFF)
	{
		ft_putchar((wc >> 18) | 0xF0);
		ft_putchar(((wc >> 12) & 0x3F) | 0x80);
		ft_putchar(((wc >> 6) & 0x3F) | 0x80);
		ft_putchar((wc & 0x3F) | 0x80);
	}
}
