# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/01 10:27:38 by fvarrin           #+#    #+#              #
#    Updated: 2021/12/02 13:06:43 by fvarrin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ROOT_DIR		?= $(shell pwd)
CLIENT_SRC_DIR		= ${ROOT_DIR}/client-srcs/
SERVER_SRC_DIR		= ${ROOT_DIR}/server-srcs/
HEADER_DIR		= ${ROOT_DIR}/includes/
LIBFT_DIR		= ${ROOT_DIR}/libft/
CLIENT_SRC		= $(addprefix ${CLIENT_SRC_DIR}, main.c)
SERVER_SRC		= $(addprefix ${SERVER_SRC_DIR}, main.c)
CLIENT_OBJ		= $(CLIENT_SRC:.c=.o)
SERVER_OBJ		= $(SERVER_SRC:.c=.o)
CLIENT_NAME		= client
SERVER_NAME		= server
NORM_BIN		= norminette
NORM_FLAGS		= -RCheckForbiddenSourceHeader -RCheckDefine
RM			= rm -f
CFLAGS			= -Wall -Wextra -Werror -I${HEADER_DIR} -I${LIBFT_DIR}/includes
CC			= gcc
LIBFT_FLAGS		= -L${LIBFT_DIR} -lft

.PHONY: 	all clean fclean re

all: 		${SERVER_NAME} ${CLIENT_NAME}

${SERVER_NAME}:	${SERVER_OBJ}
		@make -C ${LIBFT_DIR} all || true
		${CC} ${CFLAGS} ${SERVER_OBJ} ${LIBFT_FLAGS} -o ${SERVER_NAME}

${CLIENT_NAME}:	${CLIENT_OBJ}
		@make -C ${LIBFT_DIR} all || true
		${CC} ${CFLAGS} ${CLIENT_OBJ} ${LIBFT_FLAGS} -o ${CLIENT_NAME}

clean:
		${RM} ${CLIENT_OBJ}
		${RM} ${SERVER_OBJ}

fclean: 	clean
		@make -C libft fclean || true
		${RM} ${CLIENT_NAME}
		${RM} ${SERVER_NAME}

re:		fclean all

norm:		fclean
		echo "\n\n"
		${NORM_BIN} ${NORM_FLAGS} ${SRC}
