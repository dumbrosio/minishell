/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vd-ambro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:06:08 by vd-ambro          #+#    #+#             */
/*   Updated: 2023/04/03 17:06:49 by vd-ambro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ps;

	ps = (unsigned char *)s;
	c = (unsigned char)c;
	while (n && *ps != c)
	{
		ps++;
		n--;
	}
	if (n)
		return ((void *)ps);
	else
		return (NULL);
}
