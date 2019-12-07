/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 14:57:25 by aromny-w          #+#    #+#             */
/*   Updated: 2018/12/02 14:57:29 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char			*str;
	size_t			len;
	unsigned int	i;

	len = ft_strlen(s);
	if (!(str = (char *)malloc(sizeof(*str) * (len + 1))))
		return (NULL);
	i = -1;
	while (s[++i])
		str[i] = f(s[i]);
	str[i] = '\0';
	return (str);
}
