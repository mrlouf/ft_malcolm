/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:58:00 by nponchon          #+#    #+#             */
/*   Updated: 2024/09/26 17:56:06 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	This function creates a new list based on an existing one:
	- First, security check that parameters are not null
	- Second, iterate using "lst = lst->next" until last node of old list
	- Use the ft_lstnew to create new node while applying the f function
	- Security if malloc fails: clear the new list and return NULL
	- Put the newest node to the back of the list
	- Return the pointer to new_list	*/

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;

	if (!lst || !f || !del)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		new_node = ft_lstnew((*f)(lst->content));
		if (!new_node)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node);
		lst = lst->next;
	}
	return (new_list);
}

/*
#include <stdio.h>
#include <bsd/string.h>
#include "ft_lstnew_bonus.c"
#include "ft_lstadd_back_bonus.c"
#include "ft_strlen.c"
#include "ft_strdup.c"

void	*my_function(void *content)
{
	char *dest = ft_strdup(content);
	if (dest == NULL)
		return NULL;
	*dest -= 32;
	return (dest);
}

void	del(void *content)
{
	free(content);
}

int	main(void)
{
	t_list *head = malloc(sizeof(t_list));
    t_list *second = malloc(sizeof(t_list));
    t_list *third = malloc(sizeof(t_list));
	t_list *new_list;

	head->content = malloc(sizeof(char) + 5);    
	head->next = second;
    second->content = malloc(sizeof(char) + 5);
    second->next = third;
    third->content = malloc(sizeof(char) + 5);
    
	strcpy(head->content, "a");
	strcpy(second->content, "b");
	strcpy(third->content, "c");

	printf("Contenido del primer nodo: %c \n", *(char *)head->content);
	printf("Contenido del segundo nodo: %c \n", *(char *)second->content);
	printf("Contenido del tercer nodo: %c \n", *(char *)third->content);

	new_list = ft_lstmap(head, &my_function, del);
	t_list *curent = new_list;

	printf("------------------------------\n");
	printf("Contenido del primer nodo: %s \n", (char *)curent->content);
	curent = curent->next;
	printf("Contenido del segundo nodo: %s \n", (char *)curent->content);
	curent = curent->next;
	printf("Contenido del tercer nodo: %s \n", (char *)curent->content);
	ft_lstclear(&new_list, del);
	ft_lstclear(&head, del);

	return (0);
}*/
