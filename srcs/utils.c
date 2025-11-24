/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 18:38:31 by nponchon          #+#    #+#             */
/*   Updated: 2025/11/20 16:52:12 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_malcolm.h"

void    free_malcolm(t_malcolm *m)
{
    if (m->socket != -1)
        close(m->socket);
    if (m)
        free(m);
}

void	init_malcolm(char **av, t_malcolm *m)
{
    m->source_ip = av[1];
    m->source_mac = av[2];
    m->target_ip = av[3];
    m->target_mac = av[4];

    m->socket = -1;
}

void    print_arp(unsigned char *buf)
{
    struct ether_arp *arp = (struct ether_arp *)(buf + sizeof(struct ether_header));

    char sender_ip[INET_ADDRSTRLEN];
    char target_ip[INET_ADDRSTRLEN];

    inet_ntop(AF_INET, arp->arp_spa, sender_ip, sizeof(sender_ip));
    inet_ntop(AF_INET, arp->arp_tpa, target_ip, sizeof(target_ip));

    printf("ARP packet captured:\n");
    printf("  Sender MAC: %02x:%02x:%02x:%02x:%02x:%02x\n",
        arp->arp_sha[0], arp->arp_sha[1], arp->arp_sha[2],
        arp->arp_sha[3], arp->arp_sha[4], arp->arp_sha[5]);
    printf("  Sender IP: %s\n", sender_ip);
    printf("  Target MAC: %02x:%02x:%02x:%02x:%02x:%02x\n",
        arp->arp_tha[0], arp->arp_tha[1], arp->arp_tha[2],
        arp->arp_tha[3], arp->arp_tha[4], arp->arp_tha[5]);
    printf("  Target IP: %s\n", target_ip);
    printf("  Operation: %s\n",
        ntohs(arp->ea_hdr.ar_op) == ARPOP_REQUEST ? "ARP Request" : "ARP Reply");
}
