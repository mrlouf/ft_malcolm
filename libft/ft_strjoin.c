/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:09:31 by nponchon          #+#    #+#             */
/*   Updated: 2025/09/30 18:16:56 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char const *s2)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	new = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!new)
		return (NULL);
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		new[i++] = s2[j++];
	new[i] = '\0';
	return (new);
}

/*
int	main(int ac, char **av)
{
	char	*s;

	if (ac == 3)
	{
		printf("s1 = %s\n", av[1]);
		printf("s2 = %s\n", av[2]);
		s = ft_strjoin(av[1], av[2]);
		printf("%s\n", s);
		free(s);
	}
	return (0);
}*/
