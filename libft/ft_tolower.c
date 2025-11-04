/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 18:26:06 by nponchon          #+#    #+#             */
/*   Updated: 2024/09/13 18:30:47 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c += 32;
	return (c);
}
/*
int	main(void)
{
	char	c;

	c = 0;
	while (c < 127)
	{
		printf("%c = %c = %c\n", c, ft_tolower(c), tolower(c));
		c++;
	}
	return (0);
}*/
