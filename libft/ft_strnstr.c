/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:11:13 by nponchon          #+#    #+#             */
/*   Updated: 2024/09/18 15:31:40 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (little[0] == '\0')
		return ((char *)big);
	while (big[i] && i < len)
	{
		if (big[i] == little[j])
		{
			while (big[i + j] == little[j] && i + j < len)
			{
				if (little[j + 1] == '\0')
					return ((char *)&big[i]);
				j++;
			}
			j = 0;
		}
		i++;
	}
	return (NULL);
}

/*
int	main(int ac, char **av)
{
	(void) ac;
	(void) av;
	printf("ptr of match: %s\n", ft_strnstr("aaabcabcd", "aabc", -1));
	return (0);
}*/
