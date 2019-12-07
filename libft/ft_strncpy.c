/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 18:12:27 by aromny-w          #+#    #+#             */
/*   Updated: 2018/11/30 18:12:29 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	n;

	n = len;
	while (*src && len)
	{
		*dst++ = *src++;
		len--;
	}
	while (len--)
		*dst++ = '\0';
	return (dst - n);
}
