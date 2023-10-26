/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vd-ambro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 19:39:17 by vd-ambro          #+#    #+#             */
/*   Updated: 2023/04/06 19:39:41 by vd-ambro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_word(const char *s, char c)
{
	size_t	n;

	n = 0;
	while (*s)
	{
		if (*s != c)
		{
			++n;
			while (*s && *s != c)
				++s;
		}
		else
			++s;
	}
	return (n);
}

char	**ft_split(const char *s, char c)
{
	char	**arr;
	size_t	i;
	size_t	len;

	if (!s)
		return (0);
	i = 0;
	arr = malloc(sizeof(char *) * (get_word(s, c) + 1));
	if (!arr)
		return (0);
	while (*s)
	{
		if (*s != c)
		{
			len = 0;
			while (*s && *s != c && ++len)
				++s;
			arr[i++] = ft_substr(s - len, 0, len);
		}
		else
			++s;
	}
	arr[i] = 0;
	return (arr);
}
