/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 18:11:21 by aromny-w          #+#    #+#             */
/*   Updated: 2018/11/30 18:11:23 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len;

	len = ft_strlen(dst);
	while (*src && len + 1 < size)
		dst[len++] = *src++;
	dst[len] = '\0';
	return (ft_strnlen(dst, size) + ft_strlen(src));
}
