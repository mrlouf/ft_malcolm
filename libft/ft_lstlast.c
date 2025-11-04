/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:52:55 by nponchon          #+#    #+#             */
/*   Updated: 2024/09/23 18:59:18 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	This function uses a temporary pointer as a copy of a pointer to a list
	and iterates the list with the while loop until it reaches the end
	of the list, i.e. the node whose pointer "next" points to null.
	It then returns a pointer to that node.	*/

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*tmp;

	if (lst == NULL)
		return (NULL);
	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
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
	
	printf("%s\n", (char *)node1->content);
	node1 = ft_lstlast(node1);
	printf("%s\n", (char *)node1->content);
	
	return (0);
}*/
