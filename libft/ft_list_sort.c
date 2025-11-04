/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 09:48:45 by nponchon          #+#    #+#             */
/*   Updated: 2025/09/15 10:16:04 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void		ft_list_sort(t_list **lst, int (*f)(struct s_list *, struct s_list *))
{
	t_list	*current;
	t_list	*index;
	void	*temp;

	if (lst == NULL || *lst == NULL)
		return ;
	current = *lst;
	while (current != NULL)
	{
		index = current->next;
		while (index != NULL)
		{
			if ((*f)(current, index) > 0)
			{
				temp = current->content;
				current->content = index->content;
				index->content = temp;
			}
			index = index->next;
		}
		current = current->next;
	}
}