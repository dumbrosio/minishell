/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vd-ambro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:11:17 by vd-ambro          #+#    #+#             */
/*   Updated: 2023/04/04 18:29:22 by vd-ambro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	if (!src && !dest)
		return (0);
	if (dstsize == 0)
		return (ft_strlen(src));
	i = 0;
	j = 0;
	while (dest[i] && i < dstsize)
		i++;
	while ((i + j + 1) < dstsize && src[j])
	{
		dest[i + j] = src[j];
		j++;
	}
	if (i != dstsize)
		dest[i + j] = '\0';
	return (i + ft_strlen(src));
}
