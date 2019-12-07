/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putwchar_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 20:24:12 by aromny-w          #+#    #+#             */
/*   Updated: 2019/06/21 20:24:13 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putwchar_fd(wchar_t wc, int fd)
{
	if (wc <= 0x7F)
		ft_putchar_fd(wc, fd);
	else if (wc <= 0x7FF)
	{
		ft_putchar_fd((wc >> 6) | 0xC0, fd);
		ft_putchar_fd((wc & 0x3F) | 0x80, fd);
	}
	else if (wc <= 0xFFFF)
	{
		ft_putchar_fd((wc >> 12) | 0xE0, fd);
		ft_putchar_fd(((wc >> 6) & 0x3F) | 0x80, fd);
		ft_putchar_fd((wc & 0x3F) | 0x80, fd);
	}
	else if (wc <= 0x10FFFF)
	{
		ft_putchar_fd((wc >> 18) | 0xF0, fd);
		ft_putchar_fd(((wc >> 12) & 0x3F) | 0x80, fd);
		ft_putchar_fd(((wc >> 6) & 0x3F) | 0x80, fd);
		ft_putchar_fd((wc & 0x3F) | 0x80, fd);
	}
}
