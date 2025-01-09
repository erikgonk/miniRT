# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/19 12:51:14 by shurtado          #+#    #+#              #
#    Updated: 2025/01/08 13:12:30 by shurtado         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:= miniRT

SRC_D			:= ./src/
INC_D			:= ./inc/
OBJ_D			:= $(SRC_D)tmp/
LIBFT_D			:= ./lib/libft/
MLX_D			:= ./lib/MLX42/build/
VCT_D			:= ./lib/libvector/

FILES			:= main.c \
					parser/parser/parser.c \
					parser/obj/parse_obj.c parser/obj/parse_acl.c \
					parser/utils/parse_sum.c parser/utils/parse_utils.c parser/utils/parse_conversions.c parser/utils/parse_checker.c \
					parser/extra_funcs/extra_funcs.c \
					render/render/render.c \
					render/obj/cylinder.c render/obj/caps.c render/obj/cone.c render/obj/intersections.c render/obj/viewport.c \
					render/illumination/illumination.c render/illumination/specular.c\
					render/calcs/calcs.c render/calcs/quadratic.c \
					render/init/init_image.c render/init/init_rays.c render/init/init_general.c render/init/init_obj.c render/init/init_side.c render/init/init_materials.c \
					render/color/color.c render/color/checker_board.c \
					render/free/free.c \
					console/console/run_console.c \
					console/menu/submenu.c console/menu/slight_menu.c console/menu/camera_menu.c console/menu/obj_menu.c \
					debug/debug_info.c debug/print_items.c debug/time.c \
					window/mlx.c
SRCS			:= $(addprefix $(SRC_D), $(FILES))

OBJS			:= $(patsubst $(SRC_D)%.c,$(OBJ_D)%.o,$(SRCS))

CC				:= cc
IFLAGS			:= -I$(INC_D) -I$(VCT_D) -I$(LIBFT_D)inc
CFLAGS			:= -g #-fsanitize=address #-Wall -Wextra -Werror

LIB				:= lib/

LIBFT			:= libft.a
LIBVCT          := ./lib/libvector/libvct.a

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

$(OBJ_D)%.o:	$(SRC_D)%.c Makefile
			printf "\033[0;33m\r🔨 $< ✅ \033[0m"
			@mkdir -p $(dir $@)
			$(CC) $(IFLAGS) $(CFLAGS) -MMD -o $@ -c $<

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) $(LIBFT_D)$(LIBFT) $(MLX_D)$(MLX) $(LIBVCT) $(MLXFLAGS) -o $(NAME)
			# @clear

c clean:
			@make clean -s -C $(LIB)libft
			@make clean -s -C $(LIB)libvector
			@$(RM) $(DIR_MLX)/build
			${RM} ./src/tmp
			# @clear

f fclean:		clean
			@make fclean -s -C $(LIB)libft
			@make fclean -s -C $(LIB)libvector
			@${RM} ${NAME}

r re:			fclean all

v valgrind: $(NAME)
	@valgrind --leak-check=full --track-origins=yes ./$(NAME)

-include $(OBJS:.o=.d)

.PHONY:		all clean fclean re f c r libs libmlx v valgrind
