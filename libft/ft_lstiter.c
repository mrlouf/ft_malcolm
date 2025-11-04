/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:52:48 by nponchon          #+#    #+#             */
/*   Updated: 2024/09/24 18:58:50 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		(*f)(tmp->content);
		tmp = tmp->next;
	}
}

/*
void	set_zero(void *content)
{
	*(char *)content = 65;
	
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
	ft_lstiter(node1, set_zero);
	ft_lstsize(node1);
	printf("%s\n", (char *)node1->content);
	
	return (0);
}*/
