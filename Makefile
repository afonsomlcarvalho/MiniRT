# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/28 18:53:37 by gda_cruz          #+#    #+#              #
#    Updated: 2023/04/24 11:33:51 by amorais-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

####### COLORS #######
RED		=	\033[0;31m
GREEN_B	=	\033[1;32m
BLUE	=	\033[0;34m
RESET	=	\033[0m

####### DIRECTORIES #######
OBJ_DIR	=	./obj
INC_DIR	=	inc
LIB_DIR =	lib
LIBFT_DIR =	$(LIB_DIR)/libft
MLX_DIR =	$(LIB_DIR)/mlx_linux

####### COMPILER #######
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -g
LFT_FLAGS = -L$(LIBFT_DIR) -lft
MLX_FLAGS =	-L$(MLX_DIR) -lmlx_Linux -L/usr/lib -I$(MLX_DIR) -lXext -lX11 -lm -lz
OFLAGS =	-I/usr/include -I$(MLX_DIR) -O3

####### FILES #######
SRC		=	$(shell find src/ -name '*.c')
OBJ		=	$(patsubst src/%.c,$(OBJ_DIR)/%.o,$(SRC))
NAME 	=	miniRT

all: $(NAME)

$(NAME): $(OBJ)
	@make -s -C $(LIBFT_DIR)
	@printf "$(BLUE)[libft successfully compiled]\n$(RESET)"
	@make -S -C $(MLX_DIR)
	@printf "$(BLUE)[mlx successfully compiled]\n$(RESET)"
	@printf "$(BLUE)[Compiling]     "$(NAME)"$(RESET)\n"
	@$(CC) $(CFLAGS) $(OBJ) $(MLX_FLAGS) $(LFT_FLAGS) -o $(NAME)
	@printf "$(GREEN_B)[$(NAME) ready to use]\n$(RESET)"

$(OBJ_DIR)/%.o: src/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(OFLAGS) -c $< -o $@
	@printf "$(BLUE)[Compiling]     "$@"$(RESET)\n"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@make fclean -s -C $(LIBFT_DIR)
	@rm -rf $(OBJ_DIR) $(NAME)
	@echo "$(RED)[All $(NAME) files removed]$(RESET)"
	@make fclean -s -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
