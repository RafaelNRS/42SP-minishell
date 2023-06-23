CC				= gcc
CFLAGS			= -Wall -Wextra -Werror

NAME_PROJECT		= minishell

LIBFT_DIR		= ./libft/
LIBFT 			= ./libft/libft.a
HEADER_LIBFT	= ./libft/

INCLUDE_DIR		= ./include/
HEADER			= minishell.h
HEADER_PATH		= ./include/minishell.h

SRC_DIR			= ./src/
SRC_CLIENT		= minishell.c
SRC_CLIENT_PATH	= ./src/minishell.c ./src/tokenizer.c \
									./src/hash_function/add_item.c ./src/hash_function/delete_item.c ./src/hash_function/free_table.c \
									./src/hash_function/hash_functions.c ./src/hash_function/hash_table.c \
									./src/builtin/env.c ./src/builtin/exit_minishell.c \
									./src/builtin/unset.c ./src/builtin/export.c ./src/builtin/pwd.c ./src/builtin/cd.c \
									./src/builtin/echo.c \
									./src/msh_error.c ./src/execute.c \
									./src/syntax_analysis/create_cmd.c \
									./src/syntax_analysis/ft_strappend.c \
									./src/syntax_analysis/syntax_analysis.c \
									./src/syntax_analysis/validate_tokens.c \
									./src/syntax_analysis/join_n_strs.c \
									./src/execute_funcs.c \
									./src/syntax_analysis/syntax_funcs.c \
									./src/redir_aux.c \
									./src/tokenizer_aux.c \
									./src/tokenizer_aux2.c \
									./src/tokenizer_aux3.c \
									./src/tokenizer_aux4.c

BIN						= ./bin/
BINARY_OUT_PROJ		= ./bin/minishell

all: $(BINARY_OUT_PROJ)

$(BINARY_OUT_PROJ): $(SRC_CLIENT_PATH)
	@ $(MAKE) -C $(LIBFT_DIR)
	@ cp $(LIBFT) $(NAME_PROJECT)
	@ mkdir -p $(BIN)
	@ $(CC) $(CFLAGS) $(SRC_CLIENT_PATH) -I $(INCLUDE_DIR) -I $(HEADER_LIBFT) -L $(LIBFT_DIR) -lft -lreadline -o $(NAME_PROJECT)
	@ mv $(NAME_PROJECT) $(BIN)

clean:
	@ $(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	@ $(MAKE) fclean -C $(LIBFT_DIR)
	@ rm -f $(BINARY_OUT_PROJ)
	@ rm -rf $(BIN)

re: fclean all

.PHONY: all clean fclean re
