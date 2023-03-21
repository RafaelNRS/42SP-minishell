/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranascim <ranascim@42.student.42sp.org.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 08:05:02 by ranascim          #+#    #+#             */
/*   Updated: 2022/08/14 18:26:36 by ranascim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_d(int d)
{
	int			len;
	long int	d_tmp;

	d_tmp = d;
	len = 0;
	if (d_tmp < 0)
	{
		ft_putchar_fd('-', 1);
		len += ft_put_base(d_tmp * -1, 10, DECIMAL) + 1;
	}
	else
		len += ft_put_base(d_tmp, 10, DECIMAL);
	return (len);
}
