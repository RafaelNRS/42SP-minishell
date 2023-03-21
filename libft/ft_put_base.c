/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_base.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranascim <ranascim@42.student.42sp.org.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 08:23:28 by ranascim          #+#    #+#             */
/*   Updated: 2022/08/14 18:19:41 by ranascim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_put_base(unsigned long n, unsigned long n_base, char *base)
{
	int	len;

	len = 1;
	if (n >= n_base)
	{
		len = len + ft_put_base(n / n_base, n_base, base);
	}
	ft_putchar_fd(base[n % n_base], 1);
	return (len);
}
