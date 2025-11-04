/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malcolm.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 18:11:35 by nponchon          #+#    #+#             */
/*   Updated: 2025/11/04 18:40:37 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALCOLM_H
# define FT_MALCOLM_H

# include <stdio.h>
# include <stdlib.h>

void	print_usage(char *prog_name);
void	parse_malcolm(int ac, char **av);
void	init_malcolm(char **av);
void	start_malcolm();


#endif
