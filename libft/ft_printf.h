/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:10:49 by nponchon          #+#    #+#             */
/*   Updated: 2024/10/04 10:29:54 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

//	FUNCTIONS

int	ft_printf(const char *string, ...);
int	ft_converter(const char *str, int i, va_list args);
int	ft_putchar(int c);
int	ft_putstr(char *str);
int	ft_putnbr(int nbr);
int	ft_putunsigned(unsigned int nbr);
int	ft_putptr(unsigned long ptr, int i);
int	ft_puthexa(unsigned int nbr, char x);

#endif
