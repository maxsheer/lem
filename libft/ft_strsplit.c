/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 18:20:04 by aromny-w          #+#    #+#             */
/*   Updated: 2018/12/08 18:20:10 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	wcount(const char *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
			count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

static size_t	wlen(const char *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

static char		**del(char **tab, size_t i)
{
	while (i--)
		ft_strdel(&tab[i]);
	free(tab);
	tab = NULL;
	return (tab);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**tab;
	size_t	i;
	size_t	j;

	if (!(tab = (char **)malloc(sizeof(char *) * (wcount(s, c) + 1))))
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			if (!(tab[i] = (char *)malloc(sizeof(char) * (wlen(s, c) + 1))))
				return (del(tab, i));
			j = 0;
			while (*s && *s != c)
				tab[i][j++] = *s++;
			tab[i++][j] = '\0';
		}
	}
	tab[i] = NULL;
	return (tab);
}
