/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_cmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 09:56:16 by nponchon          #+#    #+#             */
/*   Updated: 2025/09/15 10:36:09 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./libft.h"

int	ft_lst_cmp(t_list *first, t_list *second)
{
	char 	*s1;
	char 	*s2;
	int		i;
	int		res;

	if (first == NULL || second == NULL)
		return (-1);
	s1 = ft_strdup((char *)first->content);
	s2 = ft_strdup((char *)second->content);
	i = -1;

	while (s1[++i]) {
		s1[i] = ft_tolower(s1[i]);
	}
	i = -1;
	while (s2[++i]) {
		s2[i] = ft_tolower(s2[i]);
	}
	
	res = strcmp(s1, s2);
	free(s1);
	free(s2);

	return (res);
}