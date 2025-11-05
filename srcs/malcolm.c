/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malcolm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 18:38:53 by nponchon          #+#    #+#             */
/*   Updated: 2025/11/05 08:05:43 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_malcolm.h"

void	start_malcolm(t_malcolm *m)
{
    (void)m;
    printf("Starting Malcolm with the following parameters:\n");
    printf("Source IP: %s\n", m->source_ip);
    printf("Source MAC: %s\n", m->source_mac);
    printf("Target IP: %s\n", m->target_ip);
    printf("Target MAC: %s\n", m->target_mac);
}
