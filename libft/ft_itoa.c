/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 17:29:02 by aromny-w          #+#    #+#             */
/*   Updated: 2018/12/10 17:29:05 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	dcount(int n)
{
	size_t	count;

	count = 1;
	while (n /= 10)
		count++;
	return (count);
}

char			*ft_itoa(int n)
{
	char	*str;
	int		sign;
	size_t	len;
	size_t	i;

	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	if ((sign = n < 0 ? -1 : 1) == -1)
		n = -n;
	len = (sign == -1 ? 1 : 0) + dcount(n);
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	str[i++] = n % 10 + '0';
	while (n /= 10)
		str[i++] = n % 10 + '0';
	if (sign == -1)
		str[i++] = '-';
	str[i] = '\0';
	return (ft_strrev(str));
}
