/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malcolm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 18:38:53 by nponchon          #+#    #+#             */
/*   Updated: 2025/11/14 13:16:16 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_malcolm.h"

void	send_arp(t_malcolm *m)
{
	(void)m;
	return ;
}

int	listen_arp(t_malcolm *m)
{
    printf("Starting Malcolm with the following parameters:\n");
    printf("Source IP: %s\n", m->source_ip);
    printf("Source MAC: %s\n", m->source_mac);
    printf("Target IP: %s\n", m->target_ip);
    printf("Target MAC: %s\n\n", m->target_mac);

    m->socket = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP));	// ETH_P_ARP to capture ARP packets only
    if (m->socket < 0) {
	    fprintf(stderr, "Error: unable to create raw socket\n");
	    return (1);
    }

    /*
    struct packet_mreq mreq = {0};
    mreq.mr_ifindex = 0;               // skip if ioctl/bind are not allowed?
    mreq.mr_type = PACKET_MR_PROMISC;
    setsockopt(m->socket, SOL_PACKET, PACKET_ADD_MEMBERSHIP, &mreq, sizeof(mreq));
    */

    unsigned char buf[65536];
    struct sockaddr_ll addr;
    socklen_t addrlen = sizeof(addr);

    printf("Starting to listen for packets between A and B...\n");

    while (42) {
        ssize_t len = recvfrom(m->socket, buf, sizeof(buf), 0,
                            (struct sockaddr*)&addr, &addrlen);
        if (len < 0) continue;

        struct ether_header *eth = (struct ether_header*)buf;
        if (ntohs(eth->ether_type) != ETH_P_ARP) continue;

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

    return (0);
}
