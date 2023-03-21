/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranascim <ranascim@42.student.42sp.org.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 21:29:04 by ranascim          #+#    #+#             */
/*   Updated: 2022/05/07 17:19:15 by ranascim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*p;
	size_t		i;

	if (start >= ft_strlen(s))
	{
		p = (char *) ft_calloc(1, sizeof(char));
		if (!p)
			return (NULL);
		else
			return (p);
	}
	i = 0;
	while (i < len && s[start + i])
		i++;
	p = (char *) ft_calloc((i + 1), sizeof(char));
	if (!p)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		p[i] = s[start + i];
		i++;
	}
	p[i] = '\0';
	return (p);
}
