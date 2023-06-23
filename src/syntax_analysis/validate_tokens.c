/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranascim <ranascim@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 12:40:00 by mariana           #+#    #+#             */
/*   Updated: 2023/06/23 18:11:34 by ranascim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
# define NEWLINE_SYNTAX "syntax error near unexpected token `newline'"

void	check_in_out_redirects(int type, t_token *token)
{
	if (!token->next)
		msh_error(2, "minishell", NEWLINE_SYNTAX);
	else if (token->prev && (token->prev->type != STRING && \
		token->prev->type < FILE && token->prev->type > END_OF_FILE))
		msh_error(2, "minishell", NEWLINE_SYNTAX);
	else if (type == REDIRECT && token->next->type != FILE)
		msh_error(2, "minishell", NEWLINE_SYNTAX);
	else if (type == REDIRECT_A && token->next->type != FILE_A)
		msh_error(2, "minishell", NEWLINE_SYNTAX);
	else if (type == INPUT && token->next->type != INPUT_FILE)
		msh_error(2, "minishell", NEWLINE_SYNTAX);
	else if (type == HEREDOC && token->next->type != END_OF_FILE)
		msh_error(2, "minishell", NEWLINE_SYNTAX);
}

void	check_tokens(t_token *token, int i)
{
	int	type;

	type = token->type;
	if (type == PIPE || type == SEMICOLON)
	{
		if (i == 0 || !token->prev)
			msh_error(2, "minishell", NEWLINE_SYNTAX);
		else if (token->prev->type != STRING && token->prev->type != FILE
			&& token->prev->type != FILE_A && token->prev->type != INPUT_FILE)
			msh_error(2, "minishell", NEWLINE_SYNTAX);
	}
	else if (type == REDIRECT || type == REDIRECT_A
		|| type == INPUT || type == HEREDOC)
		check_in_out_redirects(type, token);
}

void	validate_tokens(t_token_list *tokens_lst)
{
	t_token	*token;
	int		i;

	token = tokens_lst->head;
	i = 0;
	while (i < tokens_lst->count)
	{
		check_tokens(token, i);
		if (token->next)
			token = token->next;
		i++;
	}
}
