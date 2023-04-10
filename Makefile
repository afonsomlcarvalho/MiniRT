# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gda_cruz <gda_cruz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/28 18:53:37 by gda_cruz          #+#    #+#              #
#    Updated: 2023/03/28 20:33:18 by gda_cruz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

####### COLORS #######
RED		=	\033[0;31m
GREEN_B	=	\033[1;32m
BLUE	=	\033[0;34m
RESET	=	\033[0m

####### COMPILER #######
CC		=	c++
FLAGS	=	-Wall -Wextra -Werror -std=c++98

####### DIRECTORIES #######
OBJ_DIR	=	./obj
INC_DIR	=	inc

####### FILES #######
SRC		=	$(shell find src/ -name '*.cpp')
OBJ		=	$(patsubst src/%.cpp,$(OBJ_DIR)/%.o,$(SRC))
NAME 	=	phonebook

all: $(NAME)

$(NAME): $(OBJ)
	@printf "$(BLUE)[Compiling]     "$(NAME)"$(RESET)\n"
	@$(CC) $(OBJ) $(FLAGS) -o $(NAME)
	@printf "$(GREEN_B)[$(NAME) ready to use]\n$(RESET)"

$(OBJ_DIR)/%.o: src/%.cpp | $(OBJ_DIR)
	@$(CC) $(FLAGS) -I$(INC_DIR) -c $< -o $@
	@printf "$(BLUE)[Compiling]     "$@"$(RESET)\n"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(OBJ_DIR) $(NAME)
	@echo "$(RED)[All $(NAME) files removed]$(RESET)"

re: fclean all

.PHONY: all clean fclean re