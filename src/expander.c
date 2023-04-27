/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranascim <ranascim@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 09:07:47 by ranascim          #+#    #+#             */
/*   Updated: 2023/04/27 09:20:22 by ranascim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand(char *str, int i)
{
	int	quotes[2];
	
	quotes[0] = 0;
	quotes[1] = 0;
	while (str && str[++1])
	{
		quotes[0] = (quotes[0] + (!quotes[1] && str[i] == '\'')) % 2;
		quotes[1] = (quotes[1] + (!quotes[0] && str[i] == '\"')) % 2;
		if (!quotes[0] && str[i] == '$' && str[i + 1] && \
			((ft_strchr("/~%^{}:; ", str[i + 1]) && !quotes[1]) || \
			(ft_strchr("/~%^{}:;\"", str[i + 1]) && quotes[1])))
			
	}
}