/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 11:59:10 by nponchon          #+#    #+#             */
/*   Updated: 2024/09/24 16:06:35 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*res;
	unsigned int	i;

	i = 0;
	res = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!res)
		return (NULL);
	while (i < ft_strlen(s))
	{
		res[i] = (*f)(i, s[i]);
		i++;
	}
	res[i] = '\0';
	return (res);
}

/*
char	lower_upper(unsigned int i, char c)
{
	(void)i;
	if (c >= 'a' && c <= 'z')
		c -= 32;
	else if (c >= 'A' && c <= 'Z')
		c += 32;
	return (c);
}
int	main(void)
{
	char *str = "LoReM IpSuM";
	str = ft_strmapi(str, lower_upper);
	printf("%s\n", str);
	free(str);
}*/
