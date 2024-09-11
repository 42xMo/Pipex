/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_p.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdessm <mabdessm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:31:07 by mabdessm          #+#    #+#             */
/*   Updated: 2024/09/11 23:31:05 by mabdessm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_base_p(unsigned long nbr, char *base)
{
	int	i;

	i = 0;
	if (nbr >= (unsigned long)ft_strlen(base))
	{
		i += ft_putnbr_base_p(nbr / (unsigned long)ft_strlen(base), base);
		i += ft_putnbr_base_p(nbr % (unsigned long)ft_strlen(base), base);
	}
	if (nbr >= 0 && nbr < (unsigned long)ft_strlen(base))
		i += ft_putchar(base[nbr]);
	return (i);
}
