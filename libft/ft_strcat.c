/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amatta <amatta@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 13:05:50 by amatta            #+#    #+#             */
/*   Updated: 2023/12/02 13:06:57 by amatta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dest, char *src)
{
	char	*runner;

	runner = dest;
	while (*runner)
		runner++;
	while (*src)
		*runner++ = *src++;
	*runner = '\0';
	return (dest);
}
