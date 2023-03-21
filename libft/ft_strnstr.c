/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranascim <ranascim@42.student.42sp.org.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 20:59:07 by ranascim          #+#    #+#             */
/*   Updated: 2022/05/10 18:02:46 by ranascim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	unsigned int	i;
	unsigned int	f;

	i = 0;
	if (!*little)
		return ((char *) big);
	while (big[i] && i < len)
	{
		f = 0;
		while (big[i + f] == little[f] && (i + f) < len)
		{
			if (little[f + 1] == '\0')
				return ((char *) &big[i]);
			f++;
		}
		i++;
	}
	return (NULL);
}
