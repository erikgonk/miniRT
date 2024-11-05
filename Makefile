# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: erigonza <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/05 11:52:11 by erigonza          #+#    #+#              #
#    Updated: 2024/11/05 12:21:41 by erigonza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:= miniRT

HEAD			:= includes

SRCDIR			:= src/

LIB				:= lib/

FILES			:= main.c	

SRCS			:= $(addprefix $(SRCDIR), $(FILES))

OBJS			:= ${SRCS:.c=.o}

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

${NAME}:	${OBJS}
			@make -s -C $(LIB)libft
			@make -s -C $(LIB)libvector
			${CC} ${CFLAGS} $(OBJS) $(FLAGS) -o ${NAME}

all:		${NAME}

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
