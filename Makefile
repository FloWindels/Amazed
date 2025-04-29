##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## Makefile for the amazed program
##

SRC_MAIN	=	src/main.c

SRC_PARSER	=	src/parser/validation.c		\
				src/parser/parser.c			\
				src/parser/amazed.c

SRC_GRAPH	=	src/graph/graph.c			\
				src/graph/matrix.c

SRC_ALGO	=	src/algorithm/bfs.c			\
				src/algorithm/queue.c		\
				src/algorithm/pathfinding.c	\
				src/algorithm/robot.c		\
				src/algorithm/simulation.c	\
				src/algorithm/solver.c		\
				src/algorithm/alt_routing.c

SRC_OUTPUT	=	src/output/formatter.c

SRC_UTILS	=	src/utils/usage.c			\
				src/utils/free_memory.c		\
				src/utils/free_resource.c	\
				src/utils/path_utils.c		\
				src/utils/create_alt_path.c

SRC			=	$(SRC_PARSER)				\
				$(SRC_GRAPH)				\
				$(SRC_ALGO)					\
				$(SRC_UTILS)				\
				$(SRC_OUTPUT)

TEST_SRC 	=	tests/test_parser.c			\
				tests/test_amazed.c			\
				tests/test_validation.c		\
				tests/test_create_alt_path.c	\
				tests/test_free_memory.c	\
				tests/test_free_resource.c	\
				tests/test_path_utils.c		\
				tests/test_formatter.c		\
				tests/test_graph.c			\
				tests/test_matrix.c			\
				tests/test_alt_routing.c	\
				tests/test_bfs.c			\
				tests/test_pathfinding.c	\
				tests/test_queue.c			\
				tests/test_robot.c			\
				tests/test_simulation.c		\

OBJ			=	$(SRC:.c=.o)				\
				$(SRC_MAIN:.c=.o)

TEST_OBJ	=	$(TEST_SRC:.c=.gcno)		\
				$(TEST_SRC:.c=.gcda)

CTESTS		=	-lcriterion --coverage
CGCOVR		=	gcovr --exclude tests ; gcovr --branch --exclude tests
CFLAGS		=   -Wall -Wextra -Werror -iquote include
LIBFLAGS	=	-L lib/ -lmy
LIB_MAKE	=	make -C lib/my
RM			=	rm -f
CC			=	gcc

TEST_NAME	=	unit_tests
NAME		=	amazed

all:			clib $(NAME)

clib:
		$(LIB_MAKE)

debug: 	CFLAGS += -g
debug: 	re

$(NAME):		$(OBJ)
		$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LIBFLAGS)

$(TEST_NAME):	clean all
		$(CC) -o $(TEST_NAME) $(TEST_SRC) $(SRC) $(CTESTS)		\
		$(CFLAGS) $(LIBFLAGS)

tests_run:      $(TEST_NAME)
		./$(TEST_NAME) ; $(CGCOVR)

clean:
		$(RM) $(OBJ)
		$(RM) $(MAIN_OBJ)
		$(RM) $(TEST_OBJ)

fclean:			clean
		$(RM) $(NAME)
		$(RM) $(TEST_NAME)
		$(LIB_MAKE) fclean

re:				fclean all

.PHONY:			all clean fclean all tests_run debug
