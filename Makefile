#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edal--ce <edal--ce@sudent.42.fr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/04 14:27:31 by edal--ce          #+#    #+#              #
#    Updated: 2020/08/18 21:53:32 by edal--ce         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME		=	server
NAME2		= 	client

DIRSRC		=	src
OBJD		=	obj
INCLUDE		=	incl

SRC			=	

OBJ			=	$(SRC:.c=.o)
OBJS		=	$(OBJ:%=$(OBJD)/%)

CFLAGS		= 	-Wall -Wextra -g -fsanitize=address #-Werror 

CC			=	clang
RM			=	rm -f
ECHO		=	echo

$(NAME)		:	$(LIB) $(OBJD) $(OBJS) 
				$(CC) -I ./$(INCLUDE) $(CFLAGS) serv_main.c -o $(NAME) 

$(NAME2)		:	$(LIB) $(OBJD) $(OBJS)
				$(CC) -I ./$(INCLUDE) $(CFLAGS) client_main.c -o $(NAME2) 


$(OBJD)		:
				@mkdir $(OBJD)

$(OBJD)/%.o	:	$(DIRSRC)/%.c
				$(CC) -I ./$(INCLUDE) $(CFLAGS) -o $@ -c $<


all			:	$(NAME) $(NAME2)

clean		:
				$(RM) $(OBJS)

fclean		:	clean
				$(RM) -rf $(NAME) $(NAME2) 

bonus		:	all

re			:	fclean all

.PHONY		:	all clean re fclean $(NAME)