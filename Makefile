# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: momrane <momrane@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/08 14:34:28 by momrane           #+#    #+#              #
#    Updated: 2024/04/22 12:12:34 by momrane          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Setup
NAME 		:= minishell
CC			:= gcc
CFLAGS		:= -g3#-Wall -Wextra -Werror -g3

# Valgrind
VAL_SUPP	:= readline.supp
VAL_FLAGS	:= --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes --suppressions=$(VAL_SUPP) #--trace-children=yes

# Directories
SRC_DIR		:= ./src
BIN_DIR 	:= ./bin
INC_DIR 	:= ./inc
LIBFT_DIR	:= ./libft

# Lib
LIBFT		:= $(LIBFT_DIR)/libft.a

HEADER		:= -I $(INC_DIR)

# Colors
DEF_COLOR	:= \033[0;39m
GREEN 		:= \033[0;92m
CYAN 		:= \033[0;96m

SRC_FILES	:=	args \
				builtins \
				env_utils \
				env \
				errors \
				exec_utils \
				exec \
				expand_utils \
				expand \
				free_utils \
				free \
				ft_cd \
				ft_echo \
				ft_exit \
				ft_export \
				hd_count \
				heredocs \
				infile \
				init \
				lexer \
				main \
				multi_cmds \
				outfile \
				parser_utils \
				parser \
				pipe \
				remove \
				single_cmd_utils \
				single_cmd \
				token_check \
				token \
				utils

SRC 		:=	$(addprefix $(SRC_DIR)/, $(addsuffix .c, $(SRC_FILES)))
OBJ			:=	$(addprefix $(BIN_DIR)/, $(addsuffix .o, $(SRC_FILES)))

# Default make
all: $(NAME)

# Valgrind
val: $(NAME)
	@valgrind $(VAL_FLAGS) ./$(NAME)
	
# Compilation
$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(HEADER) $(OBJ) $(LIBFT) -o $(NAME) -lreadline
	@echo "$(GREEN)minishell compiled !$(DEF_COLOR)"

# Linking
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

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

# Non-File Targets
.PHONY:	all clean fclean re norm val


# ###########################################################
# NAME = minishell

# all: $(NAME)

# CC = cc
# CFLAGS = -Wextra -Wall -Werror

# LIB_PATH = ./libft
# LIB_Includes = $(LIB_PATH)/inc
# LIBFT = $(LIB_PATH)/libft.a

# $(LIBFT):
# 	make -sC $(LIB_PATH)

# INCLUDES = ./inc

# SRC_PATH = ./src

# INIT_PATH = $(SRC_PATH)/init
# INIT_SRC =	$(INIT_PATH)/init.c

# PARSER_PATH =	$(SRC_PATH)/parser
# PARSER_SRCS =	$(PARSER_PATH)/args.c \
# 				$(PARSER_PATH)/infile.c \
# 				$(PARSER_PATH)/outfile.c \
# 				$(PARSER_PATH)/parser_utils.c \
# 				$(PARSER_PATH)/parser.c
		
# LEXER_PATH = $(SRC_PATH)/lexer
# LEXER_SRCS =	$(LEXER_PATH)/errors.c \
# 				$(LEXER_PATH)/expand_utils.c \
# 				$(LEXER_PATH)/expand.c \
# 				$(LEXER_PATH)/lexer.c \
# 				$(LEXER_PATH)/token_check.c \
# 				$(LEXER_PATH)/token.c

# EXEC_PATH = $(SRC_PATH)/exec
# EXEC_SRCS =	$(EXEC_PATH)/builtins.c \
# 			$(EXEC_PATH)/env_utils.c \
# 			$(EXEC_PATH)/env.c \
# 			$(EXEC_PATH)/exec_utils.c \
# 			$(EXEC_PATH)/exec.c \
# 			$(EXEC_PATH)/ft_cd.c \
# 			$(EXEC_PATH)/ft_echo.c \
# 			$(EXEC_PATH)/ft_exit.c \
# 			$(EXEC_PATH)/ft_export.c \
# 			$(EXEC_PATH)/ft_unset.c \
# 			$(EXEC_PATH)/hd_count.c \
# 			$(EXEC_PATH)/heredocs.c \
# 			$(EXEC_PATH)/multi_cmds.c \
# 			$(EXEC_PATH)/pipe.c \
# 			$(EXEC_PATH)/single_cmd_utils.c \
# 			$(EXEC_PATH)/single_cmd.c

# UTILS_PATH = $(SRC_PATH)/utils
# UTILS_SRCS =	$(UTILS_PATH)/free_utils.c \
# 				$(UTILS_PATH)/free.c \
# 				$(UTILS_PATH)/remove.c \
# 				$(UTILS_PATH)/utils.c

# SRC =	$(SRC_PATH)/main.c \
# 		$(INIT_SRCS) \
# 		$(PARSER_SRCS) \
# 		$(LEXER_SRCS) \
# 		$(EXEC_SRCS) \
# 		$(UTILS_SRCS)

# # OBJ = $(addprefix $(SRC_PATH)/,$(SRC:.c=.o))
# OBJ = $(SRC:.c=.o)

# $(NAME): $(LIBFT) $(OBJ) 
# 	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) -lreadline

# %.o : %.c
# 	$(CC) -c $(CFLAGS) -I$(INCLUDES) -I$(LIB_Includes) -o $@ $<

# clean:
# 	@rm -f $(OBJ)
# 	@make -sC $(LIB_PATH) clean

# fclean: clean lib_fclean
# 	@rm -f $(NAME)
# 	@make -sC $(LIB_PATH) fclean

# re: fclean all

# .PHONY: all clean fclean re lib_clean lib_fclean
# ###########################################################