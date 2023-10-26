/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vd-ambro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:59:06 by vd-ambro          #+#    #+#             */
/*   Updated: 2023/04/03 17:03:35 by vd-ambro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ps;
	unsigned char	uc;

	ps = (unsigned char *)s;
	uc = (unsigned char)c;
	while (n > 0)
	{
		*ps = uc;
		ps++;
		n--;
	}
	return (s);
}
