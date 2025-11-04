/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 17:12:21 by nponchon          #+#    #+#             */
/*   Updated: 2024/09/13 17:15:54 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
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
		printf("%c = %d = %d\n", c, ft_isdigit(c), isdigit(c));
		c++;
	}
	return (0);
}*/
