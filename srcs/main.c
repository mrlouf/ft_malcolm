/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 18:13:50 by nponchon          #+#    #+#             */
/*   Updated: 2025/11/14 14:35:42 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_malcolm.h"

int g_sigint = 0;

int	main(int ac, char **av)
{
    if (getuid() != 0)
    {
        fprintf(stderr, "Error: This program must be run as root.\n");
        return (1);
    }
    if (ac != 5)
    {
        fprintf(stderr, "Usage: sudo  %s <source_ip> <source_mac> <target_ip> <target_mac>\n", av[0]);
        return (1);
    }

    t_malcolm *m = malloc(sizeof(t_malcolm));
    if (!m)
    {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return (1);
    }

    init_malcolm(av, m);
    if (parse_malcolm(m))
        return (free_malcolm(m), 1);
    listen_arp(m);
    free_malcolm(m);

    return (0);
}
