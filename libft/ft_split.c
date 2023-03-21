/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranascim <ranascim@42.student.42sp.org.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 10:52:44 by ranascim          #+#    #+#             */
/*   Updated: 2022/05/07 10:52:44 by ranascim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_word_count(const char *s, char c)
{
	size_t	count;
	size_t	i;
	int		word;

	count = 0;
	i = 0;
	word = 0;
	while (s[i])
	{
		if (s[i] == c)
			word = 0;
		else if (s[i] != c && word == 0)
		{
			word = 1;
			count++;
		}
		i++;
	}
	return (count);
}

static char	**ft_fill_str(char const *s, char c, char **str_arr, size_t wc)
{
	size_t	i;
	int		j;
	size_t	iwc;

	i = 0;
	iwc = 0;
	while (iwc < wc)
	{
		j = 0;
		if (s[i] != c && s[i] != '\0')
		{
			while (s[i + j] != '\0' && s[i + j] != c)
				j++;
			str_arr[iwc] = (char *) ft_calloc(j + 1, sizeof(char));
			j = 0;
			while (s[i + j] != '\0' && s[i + j] != c)
			{
				str_arr[iwc][j] = s[i + j];
				j++;
			}
			iwc++;
		}
		i = i + j + 1;
	}
	return (str_arr);
}

char	**ft_split(char const *s, char c)
{
	char	**str_arr;
	size_t	wc;

	if (!s)
		return (NULL);
	wc = ft_word_count(s, c);
	str_arr = (char **) ft_calloc(wc + 1, sizeof(char *));
	if (!str_arr)
		return (NULL);
	ft_fill_str(s, c, str_arr, wc);
	str_arr[wc] = NULL;
	return (str_arr);
}
