/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 18:38:31 by nponchon          #+#    #+#             */
/*   Updated: 2025/11/05 07:52:08 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_malcolm.h"

void	init_malcolm(char **av, t_malcolm *m)
{
    m->source_ip = av[1];
    m->source_mac = av[2];
    m->target_ip = av[3];
    m->target_mac = av[4];

    m->socket = -1;
}
