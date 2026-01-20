/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:10:53 by alacroix          #+#    #+#             */
/*   Updated: 2025/01/04 15:58:19 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stddef.h>

unsigned int	ft_str_count(const char *str);
unsigned int	ft_limit(int nbr);
int				ft_printf(const char *str, ...);
int				ft_print_address(unsigned long long nbr);
int				ft_hexa(unsigned int nbr, char mod);
int				ft_number_count(long long nbr, int base);
int				ft_hex_count(unsigned long long nbr, int base);
void			ft_putnbr(long long nbr);
void			ft_hexa_conv(unsigned long long nbr, char mod);
void			ft_codex(int nb, char mod);
void			ft_putchar(char c);

#endif
