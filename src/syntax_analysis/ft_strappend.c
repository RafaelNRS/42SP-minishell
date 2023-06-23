/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranascim <ranascim@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 12:46:32 by mariana           #+#    #+#             */
/*   Updated: 2023/06/23 13:04:22 by ranascim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_string(char *s1, char *s2)
{
	char	*new_string;
	size_t	s1_len;
	size_t	len;

	if (!s1)
		s1_len = 0;
	else
		s1_len = ft_strlen(s1);
	len = s1_len + ft_strlen(s2) + 1;
	new_string = (char *) malloc((len * sizeof(char)) + 1);
	if (new_string == NULL)
		return (NULL);
	return (new_string);
}

char	*ft_strappend(char *s1, char *s2, int space)
{
	char	*new_string;
	size_t	i;
	size_t	z;

	i = 0;
	new_string = create_string(s1, s2);
	while (s1 && s1[i])
	{
		new_string[i] = s1[i];
		i++;
	}
	if (s1 && space)
	{
		new_string[i] = ' ';
		i++;
	}
	z = 0;
	while (s2[z])
		new_string[i++] = s2[z++];
	free(s1);
	new_string[i] = '\0';
	return (new_string);
}
