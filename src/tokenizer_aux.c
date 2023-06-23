/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_aux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranascim <ranascim@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 20:36:49 by ranascim          #+#    #+#             */
/*   Updated: 2023/06/23 20:36:56 by ranascim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_delimiter(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

bool	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

bool	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

bool	is_semi(char c)
{
	return (c == ';');
}

bool	ft_isalnumvar(char c)
{
	return (ft_isdigit(c) || ft_isalpha(c) || c == '?');
}
