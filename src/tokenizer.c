/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranascim <ranascim@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 11:06:21 by ranascim          #+#    #+#             */
/*   Updated: 2023/04/16 09:32:26 by ranascim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ft_word_count(const char *s, char c, int i[3])
{
	int	quotes[2];

	quotes[0] = 0;
	quotes[1] = 0;
	while (s[i[0]])
	{
		if (s[i[0]] != c)
		{
			i[1]++;
			while ((s[i[0]] != c || quotes[0] == 1) && s[i[0]] != '\0')
			{
				if (!quotes[1] && (s[i[0]] == '\"' || s[i[0]] == '\''))
					quotes[1] = s[i[0]];
				quotes[0] = (quotes[0] + (s[i[0]] == quotes[1])) % 2;
				quotes[1] *= quotes[0] != 0;
				i[0]++;
			}
			if (quotes[0])
				return (-1);
		}
		else
			i[0]++;
	}
	return (i[1]);
}

static char	**ft_fill_str(char const *s, char c, char **str_arr, int i[3])
{
	int	s_len;
	int	quotes[2];

	quotes[0] = 0;
	quotes[1] = 0;
	s_len = ft_strlen(s);
	while (s[i[0]])
	{
		while (s[i[0]] == c && s[i[0]] != '\0')
			i[0]++;
		i[1] = i[0];
		while ((s[i[0]] != c || quotes[0] || quotes[1]) && s[i[0]])
		{
			quotes[0] = (quotes[0] + (!quotes[1] && s[i[0]] == '\'')) % 2;
			quotes[1] = (quotes[1] + (!quotes[0] && s[i[0]] == '\"')) % 2;
			i[0]++;
		}
		if (i[1] >= s_len)
			str_arr[i[2]++] = "\0";
		else
			str_arr[i[2]++] = ft_substr(s, i[1], i[0] - i[1]);
	}
	return (str_arr);
}

char **ft_tokenize(char const *cmd_line, char separator)
{
	char	**words;
	int		word_count;
	int		i[3];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	word_count = ft_word_count(cmd_line, separator, i);
	if (word_count < 1)
		return (NULL);
	words = malloc((word_count + 1) * sizeof(char *));
	if (words == NULL)
		return (NULL);
	i[0] = 0;
	i[1] = 0;
	words = ft_fill_str(cmd_line, separator, words, i);
	int j = 0;
	while (j < word_count)
	{
		ft_printf("Word %d: %s\n", j, words[j]);
		j++;
	}
	return (words);
}