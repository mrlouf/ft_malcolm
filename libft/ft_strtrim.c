/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:43:41 by nponchon          #+#    #+#             */
/*   Updated: 2024/09/24 18:19:36 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	Trim a string from characters defined in a charset:
 *	- Use ft_strchr to check current char of s1 for potential match
 *	while iterating s1
 *	- Use ft_strlen to get the length of s1 incl. potential tail-characters
 *	to trim
 *	- Use ft_strchr again from the end and decrementing so as to skip
 *	trail-characters to be trimmed
 *	- Use ft_substr to create the substring trimmed			*/

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	end;

	if (!s1 || !set)
		return (NULL);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	end = ft_strlen(s1);
	while (end && ft_strchr(set, s1[end]))
		end--;
	return (ft_substr(s1, 0, end + 1));
}

/*
int	main(int ac, char **av)
{
	char	*str;

	(void)ac;
	(void)av;
	str = ft_strtrim("  \t \t \n   \n\n\n\t", " \n\t");
	printf("str = %s\n", str);
	free(str);
	return (0);
}*/
