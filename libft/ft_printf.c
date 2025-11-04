/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:57:51 by nponchon          #+#    #+#             */
/*   Updated: 2024/10/04 10:29:41 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *string, ...)
{
	va_list	args;
	int		i;
	int		count;

	count = 0;
	i = 0;
	va_start(args, string);
	while (string[i] != '\0')
	{
		if (string[i] == '%')
		{
			count += ft_converter(string, i, args);
			i += 2;
		}
		else
			count += ft_putchar(string[i++]);
	}
	va_end(args);
	return (count);
}

/*
#include <stdio.h>
#include <limits.h>
int	main(void)
{
	//char	c = -128;
	//char	*str = NULL;
	//int		i = 102489153;
	//unsigned int		u = 4294967295;
	//void	*ptr = (void *)malloc(sizeof(char) * 8);

	printf("%d\n\n", ft_printf(" %p %p \n", LONG_MIN, LONG_MAX));
	printf("%d\n", printf(" %p %p \n", LONG_MIN, LONG_MAX));
	//free(ptr);
	return (0);
}*/
