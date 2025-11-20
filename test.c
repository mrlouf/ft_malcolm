// Debug ARP sender
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <net/ethernet.h>
#include <net/if.h>
#include <netpacket/packet.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/if_ether.h>

void send_arp_packet(
    const char *iface,
    const char *src_mac_str,
    const char *dst_mac_str,
    const char *src_ip_str,
    const char *dst_ip_str,
    int opcode // 1=request, 2=reply
) {
    int sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP));
    if (sock < 0) { perror("socket"); return; }

    struct ifreq ifr;
    strncpy(ifr.ifr_name, iface, IFNAMSIZ-1);
    if (ioctl(sock, SIOCGIFINDEX, &ifr) < 0) { perror("ioctl"); close(sock); return; }
    int ifindex = ifr.ifr_ifindex;

    unsigned char src_mac[6], dst_mac[6];
    sscanf(src_mac_str, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
        &src_mac[0], &src_mac[1], &src_mac[2], &src_mac[3], &src_mac[4], &src_mac[5]);
    sscanf(dst_mac_str, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
        &dst_mac[0], &dst_mac[1], &dst_mac[2], &dst_mac[3], &dst_mac[4], &dst_mac[5]);

    struct ether_header eth;
    memcpy(eth.ether_shost, src_mac, 6);
    memcpy(eth.ether_dhost, dst_mac, 6);
    eth.ether_type = htons(ETH_P_ARP);

    struct ether_arp arp;
    arp.ea_hdr.ar_hrd = htons(ARPHRD_ETHER);
    arp.ea_hdr.ar_pro = htons(ETH_P_IP);
    arp.ea_hdr.ar_hln = 6;
    arp.ea_hdr.ar_pln = 4;
    arp.ea_hdr.ar_op  = htons(opcode);
    memcpy(arp.arp_sha, src_mac, 6);
    inet_pton(AF_INET, src_ip_str, arp.arp_spa);
    memcpy(arp.arp_tha, dst_mac, 6);
    inet_pton(AF_INET, dst_ip_str, arp.arp_tpa);

    unsigned char packet[sizeof(struct ether_header) + sizeof(struct ether_arp)];
    memcpy(packet, &eth, sizeof(eth));
    memcpy(packet + sizeof(eth), &arp, sizeof(arp));

    struct sockaddr_ll sll = {0};
    sll.sll_ifindex = ifindex;
    sll.sll_halen = 6;
    memcpy(sll.sll_addr, dst_mac, 6);

    ssize_t sent = sendto(sock, packet, sizeof(packet), 0, (struct sockaddr*)&sll, sizeof(sll));
    if (sent < 0) perror("sendto");
    else printf("Sent ARP packet (%zd bytes) on %s\n", sent, iface);

    close(sock);
}

// Example usage:
// send_arp_packet("eth0", "aa:bb:cc:dd:ee:ff", "ff:ff:ff:ff:ff:ff", "192.168.1.10", "192.168.1.1", 2);

int main(int ac, char **av) {
    send_arp_packet(av[1], av[2], av[3], av[4], av[5], atoi(av[6]));
    return 0;
}