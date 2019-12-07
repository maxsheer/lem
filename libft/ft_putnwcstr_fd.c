/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnwcstr_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 11:06:18 by aromny-w          #+#    #+#             */
/*   Updated: 2019/06/22 11:06:19 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnwcstr_fd(const wchar_t *s, size_t n, int fd)
{
	while (*s && n)
	{
		if (*s < 128 && n >= 1)
			n--;
		else if (*s < 2048 && n >= 2)
			n -= 2;
		else if (*s < 65436 && n >= 3)
			n -= 3;
		else if (n >= 4)
			n -= 4;
		else
			break ;
		ft_putwchar_fd(*s++, fd);
	}
}
