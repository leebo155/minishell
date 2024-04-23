# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jiryu <jiryu@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/22 18:12:11 by jiryu             #+#    #+#              #
#    Updated: 2023/09/24 16:31:03 by jiryu            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror

HDRS = libft.h ft_printf.h get_next_line.h

SRCS =	ft_isalpha.c		\
		ft_isdigit.c		\
		ft_isalnum.c		\
		ft_isascii.c		\
		ft_isprint.c		\
		ft_strlen.c			\
		ft_memset.c			\
		ft_toupper.c		\
		ft_tolower.c		\
		ft_bzero.c			\
		ft_malloc.c			\
		ft_memcpy.c			\
		ft_memmove.c		\
		ft_memchr.c			\
		ft_memcmp.c			\
		ft_strchr.c			\
		ft_strrchr.c		\
		ft_strncmp.c		\
		ft_strcmp.c			\
		ft_strlcpy.c		\
		ft_strlcat.c		\
		ft_strnstr.c		\
		ft_atoi.c			\
		ft_calloc.c			\
		ft_strdup.c			\
		ft_substr.c			\
		ft_strjoin.c		\
		ft_strattach.c		\
		ft_strtrim.c		\
		ft_split.c			\
		ft_itoa.c			\
		ft_strmapi.c		\
		ft_striteri.c		\
		ft_putchar_fd.c		\
		ft_putstr_fd.c		\
		ft_putendl_fd.c		\
		ft_putnbr_fd.c 		\
		ft_lstnew.c			\
		ft_lstadd_front.c	\
		ft_lstsize.c		\
		ft_lstlast.c		\
		ft_lstadd_back.c	\
		ft_lstdelone.c		\
		ft_lstclear.c		\
		ft_lstiter.c		\
		ft_lstmap.c			\
		ft_printf.c			\
		ft_kmp.c			\
		sub_putchar_fd.c	\
		sub_putstr_fd.c		\
		sub_putnbr_fd.c		\
		sub_putunbr_fd.c	\
		sub_putlhex_fd.c	\
		sub_putuhex_fd.c	\
		sub_putptr_fd.c		\
		get_next_line.c		\
		get_next_line_utils.c
	
OBJS = $(SRCS:.c=.o)	
				
all : $(NAME) $(HDRS)

$(NAME) : $(OBJS) $(HDRS)
	ar -rcusv $(NAME) $(OBJS)

%.o : %.c
	$(CC) -c -o $@ $(CFLAGS) $<

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean
	$(MAKE) all

.PHONY : all clean fclean re