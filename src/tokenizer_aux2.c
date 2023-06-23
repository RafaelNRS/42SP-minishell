/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_aux2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranascim <ranascim@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 20:38:50 by ranascim          #+#    #+#             */
/*   Updated: 2023/06/23 20:44:29 by ranascim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_double_operator(char c1, char c2)
{
	return ((c1 == '<' && c2 == '<') || \
		(c1 == '>' && c2 == '>'));
}

void	shift_characters_right(char *line, int start, int len)
{
	int	i;

	i = len;
	while (i >= start)
	{
		line[i + 1] = line[i];
		i--;
	}
}

void	insert_single_operator_spaces(char *line, int index, int len)
{
	if (line[index + 1] != ' ' && line[index + 1] != '\0')
	{
		shift_characters_right(line, index, len);
		line[index + 1] = ' ';
	}
	if (line[index - 1] != ' ' && index > 0)
	{
		shift_characters_right(line, index - 1, len);
		line[index] = ' ';
	}
}

void	insert_double_operator_spaces(char *line, int index, int len)
{
	if (line[index + 2] != ' ' && line[index + 2] != '\0')
	{
		shift_characters_right(line, index + 1, len);
		line[index + 2] = ' ';
	}
	if (line[index - 1] != ' ' && index > 0)
	{
		shift_characters_right(line, index - 1, len);
		line[index] = ' ';
	}
}

void	insert_spaces(char *l, bool qt, int len, int i)
{
	while (i < len)
	{
		if (is_quote(l[i]))
			qt = !qt;
		if ((is_operator(l[i]) && qt == 0) || (is_semi(l[i]) && qt == 0))
		{
			if (l[i] == '|' || l[i] == ';')
				insert_single_operator_spaces(l, i, len);
			else if (l[i] == '<' || l[i] == '>')
			{
				if (is_double_operator(l[i], l[i + 1]))
				{
					insert_double_operator_spaces(l, i, len);
					i += 2;
				}
				else
					insert_single_operator_spaces(l, i, len);
			}
		}
		len = ft_strlen(l);
		i++;
	}
	l[len] = '\0';
}
