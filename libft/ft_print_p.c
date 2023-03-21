/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_p.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranascim <ranascim@42.student.42sp.org.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 08:02:00 by ranascim          #+#    #+#             */
/*   Updated: 2022/08/14 18:18:50 by ranascim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_p(unsigned long p)
{
	int	len;

	if (p == 0)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	len = 2;
	ft_putstr_fd("0x", 1);
	len += ft_put_base(p, 16, HEXLOWER);
	return (len);
}
