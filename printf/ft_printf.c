/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdessm <mabdessm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 13:44:34 by mabdessm          #+#    #+#             */
/*   Updated: 2024/08/07 19:33:14 by mabdessm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_printfpointer(unsigned long p)
{
	if (p)
	{
		ft_putstr("0x");
		return (ft_putnbr_base_p(p, "0123456789abcdef") + 2);
	}
	else
		return (ft_putstr("(nil)"));
}

static int	ft_printfpercent(char str_index, va_list args)
{
	if (str_index == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (str_index == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (str_index == 'd' || str_index == 'i')
		return (ft_putnbr(va_arg(args, int)));
	else if (str_index == 'u')
		return (ft_putunsigned(va_arg(args, unsigned int)));
	else if (str_index == 'x')
		return (ft_putnbr_base(va_arg(args, unsigned int), \
		"0123456789abcdef"));
	else if (str_index == 'X')
		return (ft_putnbr_base(va_arg(args, unsigned int), \
		"0123456789ABCDEF"));
	else if (str_index == 'p')
		return (ft_printfpointer(va_arg(args, unsigned long)));
	else if (str_index == '%')
		return (ft_putchar('%'));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		len;
	va_list	args;

	i = 0;
	len = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			len += ft_printfpercent(str[i + 1], args);
			++i;
		}
		else
			len += ft_putchar(str[i]);
		++i;
	}
	va_end(args);
	return (len);
}
