/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranascim <ranascim@42.student.42sp.org.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 07:23:58 by ranascim          #+#    #+#             */
/*   Updated: 2022/08/14 18:21:46 by ranascim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_args(va_list args, char c, int len)
{
	if (c == 'c')
	{
		ft_putchar_fd(va_arg(args, int), 1);
		len++;
	}
	if (c == 's')
		len += ft_print_s(va_arg(args, char *));
	if (c == 'p')
		len += ft_print_p(va_arg(args, unsigned long));
	if (c == 'd' || c == 'i')
		len += ft_print_d(va_arg(args, int));
	if (c == 'u')
		len += ft_put_base(va_arg(args, unsigned int), 10, DECIMAL);
	if (c == 'x')
		len += ft_put_base(va_arg(args, unsigned int), 16, HEXLOWER);
	if (c == 'X')
		len += ft_put_base(va_arg(args, unsigned int), 16, HEXUPPER);
	if (c == '%')
	{
		ft_putchar_fd('%', 1);
		len++;
	}
	return (len);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		len;
	int		i;

	i = 0;
	len = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] != '%')
		{
			ft_putchar_fd(str[i++], 1);
			len++;
		}
		else if (str[i + 1])
		{
			len = ft_print_args(args, str[i + 1], len);
			i += 2;
		}
	}
	return (len);
}
