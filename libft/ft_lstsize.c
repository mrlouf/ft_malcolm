/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:38:49 by nponchon          #+#    #+#             */
/*   Updated: 2024/09/23 18:50:41 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*somersault;
	int		i;

	somersault = lst;
	i = 0;
	while (somersault != NULL)
	{
		somersault = somersault->next;
		i++;
	}
	return (i);
}

/*
int	main(void)
{
	t_list	*node1 = ft_lstnew(strdup("first"));
	t_list	*node2 = ft_lstnew(strdup("second"));
	t_list	*node3 = ft_lstnew(strdup("third"));

	ft_lstadd_back(&node1, node2);
	ft_lstadd_back(&node1, node3);
	
	printf("%d\n", ft_lstsize(node1));
	printf("%d\n", ft_lstsize(node2));
	
	return (0);
}*/
