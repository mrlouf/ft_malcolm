/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malcolm.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 18:11:35 by nponchon          #+#    #+#             */
/*   Updated: 2025/11/05 08:04:14 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALCOLM_H
# define FT_MALCOLM_H

/* ************************************************************************** */
/*                              Libraries                                     */
/* ************************************************************************** */

# include <stdio.h>		// fprintf and family
# include <unistd.h>		// getuid
# include <stdlib.h>    	// malloc, free
# include <sys/socket.h>	// socket
# include <arpa/inet.h>		// htons and family
# include <linux/if_packet.h>	// packet memberships
# include <net/ethernet.h>

# include "../libft/libft.h"

/* ************************************************************************** */
/*                              Structs                                       */
/* ************************************************************************** */

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
int	parse_malcolm(t_malcolm *m);
int     parse_ip(char *ip);
int     parse_mac(char *mac);
void	send_arp(t_malcolm *m);
int	listen_arp(t_malcolm *m);

#endif
