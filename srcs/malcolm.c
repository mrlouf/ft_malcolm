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

    m->socket = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
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
    if (ntohs(eth->ether_type) != ETH_P_IP) continue;

    struct ip *ip_hdr = (struct ip*)(buf + sizeof(struct ether_header));

    	// Match only packets between two known IPs
	uint32_t ip1 = inet_addr(m->source_ip);
	uint32_t ip2 = inet_addr(m->target_ip);

if (ip_hdr->ip_src.s_addr == ip1 && ip_hdr->ip_dst.s_addr == ip2) 
	printf("Captured packet from A to B (%d bytes)\n", (int)len);
else if (ip_hdr->ip_src.s_addr == ip2 && ip_hdr->ip_dst.s_addr == ip1) {
	printf("Captured packet from B to A (%d bytes)\n", (int)len);
    }
}

    return (0);
}
