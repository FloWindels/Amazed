##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile for the lib compilation
##

SRC =		my_strcmp.c				\
			my_strlen.c				\
			my_putstr.c				\
			my_strdup.c				\
			long_to_str.c			\
			my_str_isnum.c			\
			rm_char_from_str.c		\
			clean_str.c				\
			my_getnbr.c				\
			my_strtok.c				\
			my_arrlen.c				\
			my_put_nbr.c			\
			my_putchar.c			\
			my_strchr.c				\

OBJ =		$(SRC:.c=.o)

CC =		gcc -c
CLIB =		ar rc
CFLAGS =	-Wall -Werror -Wextra
INCLUDE =	-iquote .
HEADER =	my.h
RM =		rm -f
CP =		cp

NAME =		libmy.a

$(NAME):	$(OBJ)
			$(CC) $(SRC) $(CFLAGS) $(INCLUDE)
			$(CLIB) $(NAME) $(OBJ)
			$(CP) $(HEADER) ../../include
			$(CP) $(NAME) ../

all:		$(NAME)

clean:
			$(RM) $(OBJ)

fclean:     clean
			$(RM) $(NAME)
			$(RM) ../$(NAME)
			$(RM) ../../include/$(HEADER)

re:			fclean all

.PHONY:		all clean fclean re
