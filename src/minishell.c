/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranascim <ranascim@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 07:31:27 by ranascim          #+#    #+#             */
/*   Updated: 2023/04/15 12:31:24 by ranascim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void msh_error(int error_code)
{
	if (error_code == 1)
		write(2,"minishell: Memory allocation error\n",35);
	else if (error_code == 2)
		write(2,"minishell: Too many arguments\n",30);

	exit(1);
}

static void sig_handler(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	read_cmd_line(char **cmd_line)
{
	char *buffer;

	buffer = "\033[1;96mminishell>";
	*cmd_line = readline(buffer);
}

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

char **ft_tokenize(char const *cmd_line, char separator)
{
	char **words;
	int	word_count;

	word_count = ft_word_count(cmd_line, separator);
	if (word_count < 1)
		return (NULL);
	words = malloc((word_count + 1) * sizeof(char *));
	if (words == NULL)
		return (NULL);
	words = ft_fill_str(cmd_line, separator, words, word_count);
	int i = 0;
}

void minishell_loop(void)
{
	char *cmd_line;
	char **tokens;
	
	while (true)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, sig_handler);
		read_cmd_line(&cmd_line);
		if (ft_strlen(cmd_line) == 0)
		{
			free(cmd_line);
			continue;
		}
		tokens = ft_tokenize(cmd_line, ' ');
		free(tokens);
		if (cmd_line)
			free(cmd_line);
		exit(0);
	}
}

int main(int argc, char **argv)
{
	if (argc > 1 && argv)
		msh_error(2);
	//TODO: Load config files
	minishell_loop();
	
	//TODO: Perform cleanup
	return 0;
}
