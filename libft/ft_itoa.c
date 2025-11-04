/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:16:40 by nponchon          #+#    #+#             */
/*   Updated: 2024/09/23 12:24:25 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	intlen(int n)
{
	int		l;

	l = 1;
	if (n < 0)
		l++;
	while ((n / 10) != 0)
	{
		n = n / 10;
		l++;
	}
	return (l);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = intlen(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len--] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	while (len > 0)
	{
		str[len] = (n % 10) + '0';
		n = n / 10;
		len--;
	}
	if (str[len] != '-')
		str[len] = (n % 10) + '0';
	return (str);
}
/*
int	main(void)
{
	char	*str;

	str = ft_itoa(-2147483648);
	printf("str = %s\n", str);
	free(str);
}*/
