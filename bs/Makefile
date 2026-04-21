##
## EPITECH PROJECT, 2026
## Makefile
## File description:
## Makefile
##


CXX 		= 	clang++

SRC			=	src/main.cpp	\
				src/Point3D.cpp 	\
				src/Ray.cpp 	\
				src/Vector.cpp 	\

OBJ			=	$(SRC:.cpp=.o)

NAME		=	bs

CXXFLAGS	=	-Wall -Wextra -std=c++20

CPPFLAGS	= 	-iquote include

all: $(NAME)

$(NAME):	$(OBJ)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re : fclean all

debug: CPPFLAGS += -g3
debug: all

.PHONY: all clean fclean re debug
