# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: erigonza <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/05 11:52:11 by erigonza          #+#    #+#              #
#    Updated: 2024/11/10 16:36:53 by erigonza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= miniRT
CC			= cc
CFLAGS		= -Wextra -Wall -Werror #-fsanitize=address
MLXFLAGS	= -ldl -lglfw -pthread -lm

#<-------------------------------|LIBRARIES|---------------------------------->#

MLX		= libmlx42.a
MLX_D	= ./lib/MLX42/build/
LIBFT	= libft.a
LIBFT_D	= ./lib/libft/

#<---------------------------------|FILES|------------------------------------>#

SRC_D	= ./src/
SRC_F	= prueba.c

OBJ_D	= ./obj/
OBJ_F	= $(SRC_F:.c=.o)
OBJ 	= $(addprefix $(OBJ_D), $(OBJ_F))

DEP_D	= ./dep/
DEP_F	= $(SRC_F:.c=.d)
DEP		= $(addprefix $(DEP_D), $(DEP_F))

#<---------------------------------|RULES|------------------------------------>#

all: libmlx libft $(NAME)

libft:
	make -C $(LIBFT_D)

libmlx: $(MLX_D)
	cmake ./lib/MLX42 -B $(MLX_D) && make -C $(MLX_D) -j4

$(OBJ_D)%.o: $(SRC_D)%.c Makefile
	$(CC) $(CFLAGS) -MMD -o $@ -c $<
	mv ${@:.o=.d} ${DEP_D}

$(NAME): $(DEP_D) $(OBJ_D) $(OBJ)
	$(CC) $(CFLAGS) $(MLXFLAGS) $(OBJ) $(MLX_D)$(MLX) $(LIBFT_D)$(LIBFT) -o $(NAME)

#<------------------------------|DIRECTORIES|--------------------------------->#

$(DEP_D):
	mkdir $(DEP_D)

$(OBJ_D):
	mkdir $(OBJ_D)

$(MLX_D):
	mkdir $(MLX_D)

#<---------------------------------|PHONY|------------------------------------>#

clean:
	rm -rf $(OBJ_D) $(DEP_D)
