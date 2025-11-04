/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 17:31:27 by nponchon          #+#    #+#             */
/*   Updated: 2024/09/13 17:34:40 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= ' ' && c <= '~')
		return (1);
	else
		return (0);
}
/*
int	main(void)
{
	unsigned char	c;

	c = 0;
	while (c <= 127)
	{
		printf("%c = %d = %d\n", c, ft_isprint(c), isprint(c));
		c++;
	}
	return (0);
}*/
