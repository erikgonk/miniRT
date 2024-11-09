# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: erigonza <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/05 11:52:11 by erigonza          #+#    #+#              #
#    Updated: 2024/11/09 16:54:42 by erigonza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:= miniRT

FILES			:= main.c	

HEAD			:= includes

LIB				:= lib/

DIR_SRC			:= ./src
SRCS			:= $(addprefix $(DIR_SRC)/, $(FILES))

DIR_OBJ			:= $(DIR_SRC)/obj

OBJS            := $(addprefix $(DIR_OBJ)/, $(FILES:.c=.o))
DEPS			:= $(addprefix $(DIR_OBJ)/, $(FILES:.c=.d))

INC				:= ./inc/miniRT.h

CC				:= gcc -g

RM				:= rm -f

CFLAGS			:= -Wall -Wextra -Werror -I $(HEAD) -D NUM_THREADS=$(NUM_THREADS)

FLAGS			:= -L $(LIB)libft -lft -L $(LIB)libvector -lvct

MACOS_MACRO		:= -D MACOS

LINUX_MACRO		:= -D LINUX

MACOS_FLAGS		:= -L $(LIB)minilibx_opengl_20191021 -lmlx -framework OpenGL -framework AppKit 

LINUX_FLAGS		:= -L $(LIB)minilibx-linux -lmlx -lm -lX11 -lXext -lpthread

UNAME			:= $(shell uname)

ifeq ($(UNAME),Darwin)
	NUM_THREADS	:= $(shell sysctl -n hw.ncpu)
	CFLAGS		+= $(MACOS_MACRO)
	FLAGS		+= $(MACOS_FLAGS)
endif
ifeq ($(UNAME),Linux)
	NUM_THREADS	:= $(shell nproc --all)
	CFLAGS		+= $(LINUX_MACRO)
	FLAGS		+= $(LINUX_FLAGS)
endif

all:		libft ${NAME}

libft:
			@make -s -C $(LIB)libft
			@make -s -C $(LIB)libvector
			@mkdir -p $(DIR_OBJ)

$(DIR_OBJ)/%.o:		$(DIR_SRC)/%.c ${INC} Makefile
			@printf "\033[0;33m\r🔨 $< ✅ \033[0m"
			@$(CC) -MMD $(CFLAGS) -c $< -o $@ 

${NAME}:	${OBJS} ${INC}
			$(CC) $(CFLAGS) $(OBJS) $(FLAGS) -o $(NAME)
			clear

c clean:
			@make clean -s -C $(LIB)libft
			@make clean -s -C $(LIB)libvector
			${RM} ${OBJS}
			clear

f fclean:		clean
			@make fclean -s -C $(LIB)libft
			@make fclean -s -C $(LIB)libvector
			@${RM} ${NAME}
			clear

r re:			fclean all

PHONY:		all clean fclean re f c r
.SILENT:
