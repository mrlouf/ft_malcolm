/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:49:37 by nponchon          #+#    #+#             */
/*   Updated: 2025/11/17 15:08:58 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
	{
		ft_printf("%s", array[i]);
		array[i + 1] ? ft_printf(" ") : ft_printf(" ");
	}
	ft_printf("\n");
}
