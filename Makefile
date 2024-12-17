# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shurtado <shurtado@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/05 11:52:11 by erigonza          #+#    #+#              #
#    Updated: 2024/12/17 10:24:18 by shurtado         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:= miniRT

SRC_D			:= ./src/
INC_D			:= ./inc/
OBJ_D			:= $(SRC_D)obj/
DEP_D			:= $(SRC_D)dep/
LIBFT_D			:= ./lib/libft/
MLX_D			:= ./lib/MLX42/build/
VCT_D			:= ./lib/libvector/

FILES			:= main.c \
				 parser/parseACL.c parser/parseSumI.c parser/parseUtils.c parser/parsing.c parser/utils.c \
				 parser/parseObj.c parser/checkerParse.c \
				 debug/ilumination.c debug/sphere.c debug/debug_info.c debug/print_items.c \
				 window/mlx.c \
				 render/calcs.c render/colour.c render/initialization.c render/intersections.c render/render.c \
				 render/rays.c render/viewport.c render/free.c \
				 render/illumination.c render/cylinder.c \
				 console/run_console.c console/submenu.c
SRCS			:= $(addprefix $(SRC_D), $(FILES))

OBJS            := $(addprefix $(OBJ_D), $(FILES:.c=.o))
DEPS			:= $(addprefix $(DEP_D), $(FILES:.c=.d))

CC				:= cc
IFLAGS			:= -I$(INC_D) -I$(VCT_D) -I$(LIBFT_D)inc
CFLAGS			:= -g -fsanitize=address #-Wall -Wextra -Werror

LIB				:= lib/

LIBFT			:= libft.a
LIBVCT          := ./lib/libvector/libvct.a

MLX				:= libmlx42.a
DIR_MLX			:= ./lib/MLX42
MLXFLAGS		:= -ldl -lglfw -pthread -lm

RM				:= rm -fr

all:		create_dirs libmlx libs $(NAME)

libmlx:
			@cmake ./lib/MLX42 -B $(MLX_D) && make -C $(MLX_D) -j4

libs:
			@make -s -C $(LIB)libft
			@make -s -C $(LIB)libvector

create_dirs:
			@mkdir -p $(OBJ_D) $(DEP_D)
			@mkdir -p $(OBJ_D)parser $(OBJ_D)debug $(OBJ_D)window $(OBJ_D)render $(OBJ_D)console

$(OBJ_D)%.o:	$(SRC_D)%.c Makefile ./inc/miniRT.h ./inc/data.h ./inc/render.h
			printf "\033[0;33m\r🔨 $< ✅ \033[0m"
			$(CC) $(IFLAGS) $(CFLAGS) -MMD -o $@ -c $<
			mv $(@:.o=.d) $(DEP_D)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) $(LIBFT_D)$(LIBFT) $(MLX_D)$(MLX) $(LIBVCT) $(MLXFLAGS) -o $(NAME)
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

-include $(OBJS:.o=.d)

PHONY:		all clean fclean re f c r libs libmlx
