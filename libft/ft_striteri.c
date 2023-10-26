/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vd-ambro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:02:01 by vd-ambro          #+#    #+#             */
/*   Updated: 2023/04/06 18:29:40 by vd-ambro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	current;

	if (!s || !f)
		return ;
	current = 0;
	while (s[current])
	{
		(*f)(current, &s[current]);
		current++;
	}
}
