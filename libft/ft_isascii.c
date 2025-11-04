/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 17:28:13 by nponchon          #+#    #+#             */
/*   Updated: 2024/09/13 17:29:16 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
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
		printf("%c = %d = %d\n", c, ft_isascii(c), isascii(c));
		c++;
	}
	return (0);
}*/
