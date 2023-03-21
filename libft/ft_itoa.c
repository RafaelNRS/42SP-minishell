/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranascim <ranascim@42.student.42sp.org.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 22:58:27 by ranascim          #+#    #+#             */
/*   Updated: 2022/05/07 22:58:27 by ranascim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_digit_count(long n)
{
	size_t	dc;

	dc = 1;
	while (n >= 10)
	{
		n = n / 10;
		dc++;
	}
	return (dc);
}

char	*ft_itoa(int n)
{
	char	*c;
	size_t	number_size;
	int		is_neg;
	size_t	i;
	long	l;

	l = n;
	is_neg = 0;
	if (n < 0)
	{
		is_neg = 1;
		l = l * -1;
	}
	number_size = ft_digit_count(l);
	c = (char *) ft_calloc(number_size + is_neg + 1, sizeof(char));
	i = 0;
	while (i < number_size)
	{
		c[number_size + is_neg - i - 1] = (l % 10) + 48;
		l = l / 10;
		i++;
	}
	if (is_neg == 1)
		c[0] = '-';
	return (c);
}
