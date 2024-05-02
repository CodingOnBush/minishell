# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: momrane <momrane@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/08 14:34:28 by momrane           #+#    #+#              #
#    Updated: 2024/05/02 09:26:39 by momrane          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Setup
NAME 		:=	minishell
CC			:=	cc
CFLAGS		:=	-Wall -Wextra -Werror -g3

# Valgrind
VAL_FLAGS	:=	--leak-check=full --show-leak-kinds=all --track-origins=yes \
				--suppressions=readline.supp

# Directories
BIN_DIR 	:=	./bin
INC_DIR 	:=	./inc
LIBFT_DIR	:=	./libft

SRC_DIR		:=	./src
INIT_DIR	:=	$(SRC_DIR)/init
LEXER_DIR	:=	$(SRC_DIR)/lexer
PARSER_DIR	:=	$(SRC_DIR)/parser
EXEC_DIR	:=	$(SRC_DIR)/exec
UTILS_DIR	:=	$(SRC_DIR)/utils

# Lib
LIBFT		:=	$(LIBFT_DIR)/libft.a

# Colors
DEF_COLOR	:=	\033[0;39m
GREEN 		:=	\033[0;92m
CYAN 		:=	\033[0;96m

INITS		:=	$(INIT_DIR)/init.c \
				$(INIT_DIR)/env_utils2.c \
				$(INIT_DIR)/env.c

LEXERS		:=	$(LEXER_DIR)/errors.c \
				$(LEXER_DIR)/expand_utils2.c \
				$(LEXER_DIR)/expand_utils.c \
				$(LEXER_DIR)/expand.c \
				$(LEXER_DIR)/lexer.c \
				$(LEXER_DIR)/token_check_utils.c \
				$(LEXER_DIR)/token_check.c \
				$(LEXER_DIR)/token.c

PARSERS		:=	$(PARSER_DIR)/args.c \
				$(PARSER_DIR)/infile.c \
				$(PARSER_DIR)/outfile.c \
				$(PARSER_DIR)/parser_utils.c \
				$(PARSER_DIR)/parser.c

EXECS		:=	$(EXEC_DIR)/builtins.c \
				$(EXEC_DIR)/env_utils.c \
				$(EXEC_DIR)/exec_utils.c \
				$(EXEC_DIR)/exec.c \
				$(EXEC_DIR)/ft_cd.c \
				$(EXEC_DIR)/ft_echo.c \
				$(EXEC_DIR)/ft_exit.c \
				$(EXEC_DIR)/ft_export_utils.c \
				$(EXEC_DIR)/ft_export.c \
				$(EXEC_DIR)/hd_count.c \
				$(EXEC_DIR)/heredocs_utils.c \
				$(EXEC_DIR)/heredocs.c \
				$(EXEC_DIR)/multi_cmds.c \
				$(EXEC_DIR)/multi_cmds_utils.c \
				$(EXEC_DIR)/pipe.c \
				$(EXEC_DIR)/single_cmd_builtin.c \
				$(EXEC_DIR)/single_cmd.c \
				$(EXEC_DIR)/get_redirs.c

UTILS		:=	$(UTILS_DIR)/free_utils.c \
				$(UTILS_DIR)/free.c \
				$(UTILS_DIR)/remove.c \
				$(UTILS_DIR)/utils.c \
				$(UTILS_DIR)/utils2.c \
				$(UTILS_DIR)/utils3.c

SRC			:=	$(SRC_DIR)/main.c $(INITS) $(LEXERS) \
				$(PARSERS) $(EXECS) $(UTILS)
OBJ			:=	$(SRC:$(SRC_DIR)/%.c=$(BIN_DIR)/%.o)

# Default make
all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) -I $(INC_DIR) $(OBJ) $(LIBFT) -lreadline -o $(NAME)
	@echo "$(GREEN)minishell compiled !$(DEF_COLOR)"

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

# libft
$(LIBFT):
	@make -C ./libft

# Clean Objects
clean:
	@make -C ./libft clean
	rm -rf $(BIN_DIR)
	@echo "$(CYAN)binary files cleaned !$(DEF_COLOR)"

# Full Clean, Objects and Binaries
fclean: clean
	@make -C ./libft fclean
	rm -f $(NAME)
	@echo "$(CYAN)exec files cleaned !$(DEF_COLOR)"

# Remake
re: fclean $(NAME)
	@echo "$(GREEN)Cleaned and rebuilt everything !$(DEF_COLOR)"

# Norminette
norm:
	@norminette $(SRC) $(INC_DIR)/*.h

# Valgrind
val: $(NAME)
	@valgrind $(VAL_FLAGS) ./$(NAME)

# Non-File Targets
.PHONY:	all clean fclean re norm val
