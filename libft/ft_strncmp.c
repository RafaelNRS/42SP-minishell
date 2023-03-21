/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranascim <ranascim@42.student.42sp.org.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 20:43:02 by ranascim          #+#    #+#             */
/*   Updated: 2022/05/04 08:07:34 by ranascim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < ft_strlen(s1) && i < ft_strlen(s2) && \
					s1[i] == s2[i] && n > i + 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
