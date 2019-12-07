/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 23:38:39 by aromny-w          #+#    #+#             */
/*   Updated: 2018/12/07 14:59:42 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char		*str;
	size_t		len;
	size_t		i;
	size_t		j;

	len = ft_strlen(s);
	while ((ft_isblank(s[len - 1]) || s[len - 1] == '\n') && len)
		len--;
	j = 0;
	while ((ft_isblank(s[j]) || s[j] == '\n') && len)
	{
		j++;
		len--;
	}
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	while (len--)
		str[i++] = s[j++];
	str[i] = '\0';
	return (str);
}
