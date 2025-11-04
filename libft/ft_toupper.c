/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 18:20:17 by nponchon          #+#    #+#             */
/*   Updated: 2024/09/13 18:31:07 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c -= 32;
	return (c);
}
/*
int	main(void)
{
	char	c;

	c = 0;
	while (c < 127)
	{
		printf("%c = %c = %c\n", c, ft_toupper(c), toupper(c));
		c++;
	}
	return (0);
}*/
