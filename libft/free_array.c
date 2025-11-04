/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:49:37 by nponchon          #+#    #+#             */
/*   Updated: 2024/11/20 16:10:03 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_array(void **array)
{
	int	i;

	if (array == NULL)
		return ;
	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
	array = NULL;
}
