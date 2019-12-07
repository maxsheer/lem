/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 16:40:29 by aromny-w          #+#    #+#             */
/*   Updated: 2018/12/17 16:40:32 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*s2;

	if (!(s2 = (char *)malloc(sizeof(char) * (n + 1))))
		return (NULL);
	ft_strncpy(s2, s1, n);
	s2[n] = '\0';
	return (s2);
}
