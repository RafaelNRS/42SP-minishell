/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariana <mariana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 10:01:47 by ranascim          #+#    #+#             */
/*   Updated: 2023/04/16 16:07:50 by mariana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>

// pq 1024 e 64?
# define MSH_LINE_BUFFER_SIZE 1024
# define MSH_TOKEN_BUFFER_SIZE 64
# define MSH_TOKEN_DELIMITER " \t\r\n\a"
# define ENV_MAX_SIZE 2

typedef struct h_item
{
	char			*key;
	char			*value;
	struct h_item	*next;
}	h_item;

typedef struct h_table
{
	h_item	**bucket_items;
	int		size;
	int		count;
}	h_table;

char **ft_tokenize(char const *cmd_line, char separator);

#endif
