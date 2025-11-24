/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 18:38:39 by nponchon          #+#    #+#             */
/*   Updated: 2025/11/24 11:00:24 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_malcolm.h"

/* 
    Using the UNIX standard for 48-bit MAC addresses: six groups of two hexadecimal digits,
    separated by colons (e.g., 00:1A:2B:3C:4D:5E).
*/
int parse_mac(char *mac)
{
    char    **bytes;
    int     i;

    bytes = ft_split(mac, ':');
    if (!bytes)
    {
        fprintf(stderr, "Error: Memory allocation failed while parsing MAC.\n");
        return (1);
    }
    i = 0;
    while (bytes[i])
    {
        if (ft_strlen(bytes[i]) != 2 || !ft_isxdigit(bytes[i][0]) || !ft_isxdigit(bytes[i][1]))
        {
            free_array((void **)bytes);
            return (1);
        }
        i++;
    }
    if (i != 6)
    {
        free_array((void **)bytes);
        return (1);
    }
    free_array((void **)bytes);
    return (0);
}

static int ft_isdigit_str(char *str)
{
    int i = 0;
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}

/* 
    Simple IPv4 validation: four octets separated by dots, each ranging from 0 to 255.
*/
int parse_ip(char *ip)
{
    char    **octets;
    int     i;
    int     octet_value;

    octets = ft_split(ip, '.');
    if (!octets)
    {
        fprintf(stderr, "Error: Memory allocation failed while parsing IP.\n");
        return (1);
    }
    i = 0;
    while (octets[i])
    {
        if (!ft_isdigit_str(octets[i]))
        {
            free_array((void **)octets);
            return (1);
        }
        octet_value = ft_atoi(octets[i]);
        if (octet_value < 0 || octet_value > 255)
        {
            free_array((void **)octets);
            return (1);
        }
        i++;
    }
    if (i != 4)
    {
        free_array((void **)octets);
        return (1);
    }
    free_array((void **)octets);
    return (0);
}

int parse_malcolm(t_malcolm *m)
{
    if (parse_ip(m->source_ip)){
        fprintf(stderr, "Error: Invalid source IP address: %s \n", m->source_ip);
        return (1);
    }
    if (parse_mac(m->source_mac)) {
        fprintf(stderr, "Error: Invalid source MAC address: %s \n", m->source_mac);
        return (1);
    }
    if (parse_ip(m->target_ip)){
        fprintf(stderr, "Error: Invalid target IP address: %s \n", m->target_ip);
        return (1);
    }
    if (parse_mac(m->target_mac)){
        fprintf(stderr, "Error: Invalid target MAC address: %s \n", m->target_mac);
        return (1);
    }
	if (m->verbose < 0) {
		fprintf(stderr, "Error: Unknown flag\n");
		return (1);
	}
    return (0);
}
