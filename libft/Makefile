# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: momrane <momrane@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/17 15:35:38 by momrane           #+#    #+#              #
#    Updated: 2024/03/12 16:35:20 by momrane          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Archive name
NAME	:=	libft.a

# Directories
SRC_DIR :=	./src
BIN_DIR :=	./bin
INC_DIR :=	./inc

# Compilation
AR 		:=	ar rcs
CC 		:=	cc
FLAGS 	:=	-Wall -Werror -Wextra
HEADER	:=	$(INC_DIR)/libft.h

# Sources
SRC 	:=	$(wildcard $(SRC_DIR)/*.c)

# Binaries
OBJ 	:=	$(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%.o, $(SRC))

# Default make
all: $(NAME)

# Creating archive
$(NAME): $(OBJ)
	@$(AR) $@ $^

# Linking
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER)
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) -c $< -o $@

# Clean binaries
clean:
	@rm -rf $(BIN_DIR)

# Clean binaries and libraries
fclean: clean
	@rm -rf $(NAME)

# remake
re: fclean all

.PHONY: all clean fclean re
