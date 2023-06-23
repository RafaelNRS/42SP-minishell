/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_aux3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranascim <ranascim@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 20:39:57 by ranascim          #+#    #+#             */
/*   Updated: 2023/06/23 20:40:24 by ranascim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_s_quote(char *input, bool quotes[2])
{
	if (*input == '\'' && !quotes[1])
		return (!quotes[0]);
	else
		return (quotes[0]);
}

bool	check_d_quote(char *input, bool quotes[2])
{
	if (*input == '\"' && !quotes[0])
		return (!quotes[1]);
	else
		return (quotes[1]);
}

char	*remove_outer_quotes(char *str)
{
	int		len;
	char	*result;
	int		i;
	char	quote;

	i = 0;
	result = str;
	len = ft_strlen(str);
	while (i < len)
	{
		if (is_quote(str[i]))
		{
			quote = str[i++];
			while (i < len && str[i] != quote)
				*result++ = str[i++];
			if (i < len)
				i++;
		}
		else
			*result++ = str[i++];
	}
	*result = '\0';
	return (str);
}

void	copy_variable_value(char *var_name, char **out_ptr)
{
	char	*var_value;

	if (var_name[0] != '?')
		var_value = ht_search(var_name);
	else
		var_value = ft_itoa(g_msh.error_code);
	if (var_value)
	{
		ft_strlcpy(*out_ptr, var_value, ft_strlen(var_value) + 1);
		*out_ptr += ft_strlen(var_value);
	}
}

void	handle_var_exp(const char **in_ptr, char *var, char **out, bool s_quote)
{
	char	*var_name_ptr;

	if (**in_ptr == '$' && !s_quote && ft_isalnumvar(*(*in_ptr + 1)))
	{
		(*in_ptr)++;
		var_name_ptr = var;
		while (**in_ptr && (!is_quote(**in_ptr) && !is_delimiter(**in_ptr)))
			*var_name_ptr++ = *(*in_ptr)++;
		*var_name_ptr = '\0';
		copy_variable_value(var, out);
	}
	else if (**in_ptr == '~' && !s_quote)
	{
		(*in_ptr)++;
		ft_strlcpy(*out, ht_search("HOME"), ft_strlen(ht_search("HOME")) + 1);
		*out += ft_strlen(ht_search("HOME"));
	}
	else
		*(*out)++ = *(*in_ptr)++;
}
