/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@42.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 16:47:56 by nponchon          #+#    #+#             */
/*   Updated: 2024/11/09 16:48:02 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_digit(char c, int digits_in_base)
{
	int	max_digit;

	if (digits_in_base <= 10)
		max_digit = digits_in_base - 1 + '0';
	else
		max_digit = digits_in_base - 10 - 1 + 'a';
	if (c >= '0' && c <= '9' && c <= max_digit)
		return (c - '0');
	else if (c >= 'a' && c <= 'f' && c <= max_digit)
		return (10 + c - 'a');
	else
		return (-1);
}

int	ft_atoi_base(char *str, int base)
{
	int	result;
	int	sign;
	int	digit;
	int	i;

	result = 0;
	sign = 1;
	i = -1;
	if (str == NULL || base < 2 || base > 16)
		return (0);
	if (str[++i] == '-')
		sign = -1;
	while (str[++i])
	{
		digit = get_digit(ft_tolower(*str), base);
		if (digit == -1)
			break ;
		result = result * base + digit;
	}
	return (result * sign);
}
