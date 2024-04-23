# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jiryu <jiryu@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/11 16:14:19 by jiryu             #+#    #+#              #
#    Updated: 2023/09/28 13:10:35 by jiryu            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = src/main.c						\
		src/init/init.c					\
		src/utils/utils_1.c				\
		src/minishell/minishell.c		\
		src/chunk/chunk_1.c				\
		src/chunk/chunk_2.c				\
		src/chunk/chunk_3.c				\
		src/cmd/cmd_1.c					\
		src/cmd/cmd_2.c					\
		src/cmd/cmd_3.c					\
		src/cmd/cmd_4.c					\
		src/builtin/my_echo.c			\
		src/builtin/my_cd_1.c			\
		src/builtin/my_cd_2.c			\
		src/builtin/my_env.c			\
		src/builtin/my_exit.c			\
		src/builtin/my_pwd.c			\
		src/builtin/my_unset_1.c		\
		src/builtin/my_unset_2.c		\
		src/builtin/my_export_1.c		\
		src/builtin/my_export_2.c		\
		src/builtin/my_export_3.c		\
		src/signal/signal.c				\
		src/execute/execute_1.c			\
		src/execute/execute_2.c			\
		src/execute/execute_3.c			\
		src/execute/execute_4.c			\
		src/dollar/dollar_1.c			\
		src/dollar/dollar_2.c			\
		src/dollar/dollar_3.c
		
OBJS = $(SRCS:.c=.o)

HDRS = hdr/minishell.h

CC = cc
CFLAGS = -Wall -Wextra -Werror


RM = rm -f

LIBFT = ./libft/libft.a
DIR_LIBFT = ./libft/
INC_OPT = -L./libft/ -lft -lreadline -lhistory


all : $(NAME)

$(NAME) : $(LIBFT) $(OBJS) $(HDRS)
	$(CC) $(CFLAGS) $(INC_OPT) -o $@ $(OBJS)

$(LIBFT) :
	$(MAKE) -C $(DIR_LIBFT) all
	$(MAKE) -C $(DIR_LIBFT) clean

%.o : %.c
	$(CC) $(CFLAGS) -I./hdr/  -I./libft/ -c -o $@ $<

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME) ./.tmp_heredoc_file_*
	$(MAKE) -C $(DIR_LIBFT) fclean

re : fclean
	$(MAKE) all

.PHONY : all fclean clean re
