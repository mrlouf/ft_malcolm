/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malcolm.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 18:11:35 by nponchon          #+#    #+#             */
/*   Updated: 2025/11/14 12:51:26 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALCOLM_H
# define FT_MALCOLM_H

/* ************************************************************************** */
/*                              Libraries                                     */
/* ************************************************************************** */

# include <stdio.h>		        // fprintf and family
# include <unistd.h>		    // getuid
# include <stdlib.h>    	    // malloc, free
# include <sys/socket.h>	    // socket
# include <arpa/inet.h>		    // htons and family
# include <linux/if_packet.h>	// packet memberships
//# include <net/ethernet.h>
//# include <netinet/in.h>      // compatibility?
//# include <netinet/ip.h>      // compatibility?
# include <netinet/if_ether.h>  // ARP packet structure

# include "../libft/libft.h"

/* ************************************************************************** */
/*                              Structs                                       */
/* ************************************************************************** */

/*
    ARP packet structure, as defined in <netinet/if_ether.h>

typedef struct ether_arp {
    u_short ea_hdr.ar_hrd;      // Hardware type
    u_short ea_hdr.ar_pro;      // Protocol type
    u_char  ea_hdr.ar_hln;      // Hardware address length
    u_char  ea_hdr.ar_pln;      // Protocol address length
    u_short ea_hdr.ar_op;       // Operation (request/reply)
    u_char  arp_sha[6];         // Sender hardware address (MAC)
    u_char  arp_spa[4];         // Sender protocol address (IP)
    u_char  arp_tha[6];         // Target hardware address (MAC)
    u_char  arp_tpa[4];         // Target protocol address (IP)
};
*/

typedef struct s_malcolm
{
    char    *source_ip;
    char    *source_mac;
    char    *target_ip;
    char    *target_mac;

    int	socket;

}   t_malcolm;

/* ************************************************************************** */
/*                              Globals                                       */
/* ************************************************************************** */

extern int g_sigint;

/* ************************************************************************** */
/*                              Functions                                     */
/* ************************************************************************** */

void	init_malcolm(char **av, t_malcolm *m);
int     parse_malcolm(t_malcolm *m);
int     parse_ip(char *ip);
int     parse_mac(char *mac);
void	send_arp(t_malcolm *m);
int	    listen_arp(t_malcolm *m);

#endif
