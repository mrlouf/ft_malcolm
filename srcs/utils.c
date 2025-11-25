/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 18:38:31 by nponchon          #+#    #+#             */
/*   Updated: 2025/11/24 10:58:24 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_malcolm.h"

void    free_malcolm(t_malcolm *m)
{
    if (m->socket != -1) {
        close(m->socket);
		m->socket = -1;
	}
    if (m) {
        free(m);
		m = NULL;
	}
}

static int		hexvalue(const char c)
{
	if (c >= '0' && c <= '9') return (c - '0');
	if (c >= 'a' && c <= 'f') return (c - 'a' + 10);
	if (c >= 'A' && c <= 'F') return (c - 'A' + 10);
	return -1;
}

void	set_sourcemac(t_malcolm *m, unsigned char *ptr)
{
	char *str = m->source_mac;
	int hi, lo;
	int count = 0;

	while (*str)
	{
		if (*str == ':') {
			str++; 
		} else {
			hi = hexvalue(*str++);
			lo = hexvalue(*str++);
			ptr[count++] = (hi << 4) | lo;
		}
	}
}

int		set_socket(t_malcolm *m)
{
    int sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP));	// ETH_P_ARP to capture ARP packets only
    if (sock < 0) {
	    fprintf(stderr, "Error: unable to create raw socket\n");
	    return (free_malcolm(m), 1);
    }

	if (setsockopt(sock, SOL_SOCKET, SO_BINDTODEVICE, "eth0", strlen("eth0")) < 0) {
        fprintf(stderr, "Error: setsockopt SO_BINDTODEVICE failed\n");
        return (free_malcolm(m), 1);
    }

	struct timeval	timeout;
	timeout.tv_sec = 0;
	timeout.tv_usec = 100;
	if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof timeout)) {
		fprintf(stderr, "Error: setsockopt SO_BINDTODEVICE failed\n");
        return (free_malcolm(m), 1);
    }
	
	m->socket = sock;
	return (0);
}

void	init_malcolm(char **av, t_malcolm *m)
{
    m->source_ip = av[1];
    m->source_mac = av[2];
    m->target_ip = av[3];
    m->target_mac = av[4];

	if (!av[5]) {
		m->verbose = 0;
		return ;
	}

	m->verbose = ft_strcmp(av[5], "-v") == 0 ? 1 : -1;
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
