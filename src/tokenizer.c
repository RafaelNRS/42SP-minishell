/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranascim <ranascim@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 08:51:20 by ranascim          #+#    #+#             */
/*   Updated: 2023/06/23 20:42:08 by ranascim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	define_operator(char *token)
{
	if (!(ft_strncmp(token, "|", 1)))
		return (PIPE);
	if (is_double_operator(token[0], token[1]))
	{
		if (!(ft_strncmp(token, ">", 1)))
			return (REDIRECT_A);
		if (!(ft_strncmp(token, "<", 1)))
			return (HEREDOC);
	}
	if (!(ft_strncmp(token, ">", 1)))
		return (REDIRECT);
	if (!(ft_strncmp(token, "<", 1)))
		return (INPUT);
	return (false);
}

static void	define_type(t_token **token)
{
	int	prev_type;

	prev_type = 0;
	if ((*token)->prev && (*token)->prev->type)
		prev_type = (*token)->prev->type;
	if (is_operator((*token)->token[0]))
		(*token)->type = define_operator((*token)->token);
	else if (is_semi((*token)->token[0]))
		(*token)->type = SEMICOLON;
	else if (prev_type == REDIRECT)
		(*token)->type = FILE;
	else if (prev_type == REDIRECT_A)
		(*token)->type = FILE_A;
	else if (prev_type == INPUT)
		(*token)->type = INPUT_FILE;
	else if (prev_type == HEREDOC)
		(*token)->type = END_OF_FILE;
	else
		(*token)->type = STRING;
}

void	ft_tokenize(char *p, t_token_list **list, bool quotes[2], char *t_st)
{
	while (*p)
	{
		quotes[0] = check_s_quote(p, quotes);
		quotes[1] = check_d_quote(p, quotes);
		if (is_delimiter(*p) && !quotes[0] && !quotes[1])
		{
			if (t_st)
			{
				*p = '\0';
				if ((*list)->count++ < MAX_TOKENS)
					add_token((*list), \
					new_token(expand_variables(t_st, false)));
				t_st = NULL;
			}
		}
		else if (!t_st)
			t_st = p;
		p++;
	}
	if (t_st && (*list)->count++ < MAX_TOKENS)
		add_token((*list), new_token(expand_variables(t_st, false)));
}

static void	define_types(t_token_list **list)
{
	t_token	*current;

	current = (*list)->head;
	while (current != NULL)
	{
		define_type(&current);
		current = current -> next;
	}
}

t_token_list	*ft_init_tokenize(char *input)
{
	t_token_list	*list;
	bool			quotes[2];
	char			*token_start;
	int				len;
	int				i;

	i = 0;
	list = new_token_list();
	if (!list)
		return (NULL);
	len = ft_strlen(input);
	token_start = NULL;
	quotes[0] = false;
	quotes[1] = false;
	insert_spaces(input, false, len, i);
	ft_tokenize(input, &list, quotes, token_start);
	define_types(&list);
	return (list);
}
