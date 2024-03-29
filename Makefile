# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/08 14:34:28 by momrane           #+#    #+#              #
#    Updated: 2024/03/28 12:58:08 by vvaudain         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Setup
NAME 		:= minishell
CC			:= cc
CFLAGS		:= -g3#-Wall -Wextra -Werror -g3

# Valgrind
VAL_SUPP	:= readline.supp
VAL_FLAGS	:= --leak-check=full --show-leak-kinds=all --track-fds=yes --suppressions=$(VAL_SUPP)

# Directories
SRC_DIR		:= ./src
BIN_DIR 	:= ./bin
INC_DIR 	:= ./inc
LIBS_DIR 	:= ./lib
LIBFT_DIR	:= ./libft

# Lib
LIBFT		:= $(LIBFT_DIR)/libft.a

HEADER		:= -I $(INC_DIR)

# Colors
DEF_COLOR	:= \033[0;39m
GREEN 		:= \033[0;92m
CYAN 		:= \033[0;96m

#Sources
SRC_FILES 	:=	main utils free token token_check signals \
				parser args infile outfile data print check \
				errors exec builtins expand
SRC 		:= $(addprefix $(SRC_DIR)/, $(addsuffix .c, $(SRC_FILES)))
OBJ			:= $(addprefix $(BIN_DIR)/, $(addsuffix .o, $(SRC_FILES)))

# Default make
all: $(NAME)
	@./$(NAME)

# Valgrind
val: $(NAME)
	@valgrind $(VAL_FLAGS) ./$(NAME)
	
# Compilation
$(NAME): $(OBJ) $(LIBFT)
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
.PHONY:	all clean fclean re norm