# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: erigonza <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/05 11:52:11 by erigonza          #+#    #+#              #
#    Updated: 2024/11/18 17:15:26 by erigonza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:= miniRT

SRC_D			:= ./src/
OBJ_D			:= $(SRC_D)obj/
DEP_D			:= $(SRC_D)dep/
LIBFT_D			:= ./lib/libft/
MLX_D			:= ./lib/MLX42/build/

FILES			:= main.c lib.c sphere.c mlx.c ilumination.c
SRCS			:= $(addprefix $(SRC_D), $(FILES))

OBJS            := $(addprefix $(OBJ_D), $(FILES:.c=.o))
DEPS			:= $(addprefix $(DEP_D), $(FILES:.c=.d))

CC				:= cc
CFLAGS			:= -g  -fsanitize=address #-Wall -Wextra -Werror

LIB				:= lib/

LIBFT			:= libft.a

MLX				:= libmlx42.a
DIR_MLX			:= ./lib/MLX42
MLXFLAGS		:= -ldl -lglfw -pthread -lm

RM				:= rm -fr

all:		libmlx libs $(NAME)

libmlx:
			@cmake ./lib/MLX42 -B $(MLX_D) && make -C $(MLX_D) -j4

libs:
			@make -s -C $(LIB)libft
			@make -s -C $(LIB)libvector
			@mkdir -p $(OBJ_D) $(DEP_D)

$(OBJ_D)%.o:	$(SRC_D)%.c Makefile
			@printf "\033[0;33m\r🔨 $< ✅ \033[0m"
			@$(CC) $(CFLAGS) -MMD -o $@ -c $<
			@mv $(@:.o=.d) $(DEP_D)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(MLXFLAGS) $(OBJS) $(MLX_D)$(MLX) $(LIBFT_D)$(LIBFT) -o $(NAME)
			clear

c clean:
			@make clean -s -C $(LIB)libft
			@make clean -s -C $(LIB)libvector
			@$(RM) $(DIR_MLX)/build
			${RM} ./src/obj ./src/dep
			clear

f fclean:		clean
			@make fclean -s -C $(LIB)libft
			@make fclean -s -C $(LIB)libvector
			@${RM} ${NAME}

r re:			fclean all

PHONY:		all clean fclean re f c r libs libmlx
.SILENT:
