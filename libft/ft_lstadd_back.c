/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 19:00:25 by nponchon          #+#    #+#             */
/*   Updated: 2024/09/23 19:16:31 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	This function takes a new, independent node and add it to the last
	position of an existing list.
	If the new node is empty, the function ends.
	If the existing list is empty, it sets the new node as the first node.
	Otherwise, it uses a temp copy of the list to go to the last node and
	set its pointer "next" to the new node.		*/

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = ft_lstlast(*lst);
	tmp->next = new;
	return ;
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
