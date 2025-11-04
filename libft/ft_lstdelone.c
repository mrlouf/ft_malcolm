/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 19:17:44 by nponchon          #+#    #+#             */
/*   Updated: 2024/09/23 19:21:18 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	This function simply uses a deleting function to empty the content of a node
	before freeing the pointer to that node.		*/

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	(*del)(lst->content);
	free(lst);
	return ;
}

/*
void	delete(void *content)
{
	*(char *)content = 0;
	return ;
}

int	main(void)
{
	t_list	*node1 = ft_lstnew(strdup("first"));
	t_list	*node2 = ft_lstnew(strdup("second"));
	t_list	*node3 = ft_lstnew(strdup("third"));
	t_list	*node4 = ft_lstnew(strdup("fourth"));

	ft_lstadd_back(&node1, node2);
	ft_lstadd_back(&node1, node3);
	ft_lstadd_back(&node1, node4);
	
	printf("%d\n", ft_lstsize(node1));
	printf("%d\n", ft_lstsize(node2));
	printf("%d\n", ft_lstsize(node3));
	printf("%d\n", ft_lstsize(node4));
	
	printf("%s\n", (char *)node1->content);
	ft_lstdelone(node4, delete);
	node3->next = NULL;
	printf("%d\n", ft_lstsize(node1));
	//node1 = ft_lstlast(node1);
	printf("%s\n", (char *)node1->content);
	
	return (0);
}*/
