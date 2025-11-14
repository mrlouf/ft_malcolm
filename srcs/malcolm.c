/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malcolm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 18:38:53 by nponchon          #+#    #+#             */
/*   Updated: 2025/11/14 14:32:45 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_malcolm.h"

extern int g_sigint;

void	send_arp(t_malcolm *m, unsigned char *buf)
{
	(void)m;

	struct ether_arp *arp = (struct ether_arp *)(buf + sizeof(struct ether_header));
	char sender_ip[INET_ADDRSTRLEN];
    char target_ip[INET_ADDRSTRLEN];

    inet_ntop(AF_INET, arp->arp_spa, sender_ip, sizeof(sender_ip));
    inet_ntop(AF_INET, arp->arp_tpa, target_ip, sizeof(target_ip));
	printf("Sending forged ARP reply to %s\n", target_ip);

	return ;
}

int	listen_arp(t_malcolm *m)
{
    m->socket = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP));	// ETH_P_ARP to capture ARP packets only
    if (m->socket < 0) {
	    fprintf(stderr, "Error: unable to create raw socket\n");
	    return (free_malcolm(m), 1);
    }

	// This might not be necessary since we need to send a reply at the first ARP request, ie. ignore container B's reply.
    struct packet_mreq mreq = {0};
    mreq.mr_ifindex = 0;	// 0 means all interfaces
    mreq.mr_type = PACKET_MR_PROMISC;	// set promiscuous mode to capture also non-broadcast packets, eg. unicast ARP replies 
    setsockopt(m->socket, SOL_PACKET, PACKET_ADD_MEMBERSHIP, &mreq, sizeof(mreq));

    unsigned char buf[65536];
    struct sockaddr_ll addr;
    socklen_t addrlen = sizeof(addr);

    printf("Starting to listen for packets between A and B...\n");

    while (g_sigint == 0) {
        ssize_t len = recvfrom(m->socket, buf, sizeof(buf), 0,
                            (struct sockaddr*)&addr, &addrlen);
        if (len < 0)
			continue;

        struct ether_header *eth = (struct ether_header*)buf;
        if (ntohs(eth->ether_type) == ETH_P_ARP) 
			break;
    }

	print_arp(buf);
	send_arp(m, buf);

    return (0);
}
