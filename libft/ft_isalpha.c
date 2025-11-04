/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 17:09:00 by nponchon          #+#    #+#             */
/*   Updated: 2024/09/24 19:00:26 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Simply returns 1 if the character is alphabetical
or 0 if it is not.
*/
int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/*
int	main(void)
{
	int	c;

	c = 99;
	while (c < 100)
	{
		printf("%c = %d = %d\n", c, ft_isalpha(c), isalpha(c));
		c++;
	}
	return (0);
}*/
